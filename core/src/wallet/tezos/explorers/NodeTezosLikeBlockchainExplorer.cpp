/*
 *
 * NodeTezosLikeBlockchainExplorer
 *
 * Created by El Khalil Bellakrid on 29/04/2019.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ledger
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */


#include "NodeTezosLikeBlockchainExplorer.h"
#include <wallet/tezos/explorers/api/TezosLikeTransactionsParser.h>
#include <wallet/tezos/explorers/api/TezosLikeTransactionsBulkParser.h>
#include <wallet/tezos/explorers/api/TezosLikeBlockParser.h>
#include <api/ErrorCode.hpp>
#include <api/TezosConfigurationDefaults.hpp>
#include <api/Configuration.hpp>
#include <utils/Exception.hpp>
#include <rapidjson/document.h>

namespace ledger {
    namespace core {

        NodeTezosLikeBlockchainExplorer::NodeTezosLikeBlockchainExplorer(
                const std::shared_ptr<api::ExecutionContext> &context,
                const std::shared_ptr<HttpClient> &http,
                const api::TezosLikeNetworkParameters &parameters,
                const std::shared_ptr<api::DynamicObject> &configuration)
            : TezosLikeBlockchainExplorer(
                context, http, parameters, configuration,
                {api::Configuration::BLOCKCHAIN_EXPLORER_API_ENDPOINT})
        {
            _explorerVersion = configuration->getString(api::Configuration::BLOCKCHAIN_EXPLORER_VERSION)
                    .value_or(api::TezosConfigurationDefaults::TEZOS_DEFAULT_API_VERSION);
        }


        Future<std::shared_ptr<BigInt>>
        NodeTezosLikeBlockchainExplorer::getBalance(const TezosLikeKeychain::Address &address) const {
            bool parseNumbersAsString = true;
            const auto addressStr = address->toString();
            return _http->GET(fmt::format("blockchain/{}/{}/balance/{}",
                                          getExplorerVersion(),
                                          getNetworkParameters().Identifier,
                                          addressStr))
                    .json(parseNumbersAsString)
                    .mapPtr<BigInt>(getContext(), [addressStr](const HttpRequest::JsonResult &result) {
                        auto &json = *std::get<1>(result);
                        if (!json.IsArray() && json.Size() == 1 && json[0].IsString()) {
                            throw make_exception(api::ErrorCode::HTTP_ERROR, "Failed to get balance for {}", addressStr);
                        }
                        auto info = json[0].GetString();
                        return std::make_shared<BigInt>(info);
                    });
        }

        Future<std::shared_ptr<BigInt>>
        NodeTezosLikeBlockchainExplorer::getFees() const {
            bool parseNumbersAsString = true;
            return _http->GET(fmt::format("blockchain/{}/{}/head", getExplorerVersion(), getNetworkParameters().Identifier))
                    .json(parseNumbersAsString).mapPtr<BigInt>(getContext(), [](const HttpRequest::JsonResult &result) {
                        auto &json = *std::get<1>(result);
                        //Is there a fees field ?
                        if (!json.IsObject() || !json.HasMember("fees") ||
                            !json["fees"].IsString()) {
                            throw make_exception(api::ErrorCode::HTTP_ERROR,
                                                  "Failed to get fees from network, no (or malformed) field \"result\" in response");
                        }
                        std::string fees = json["fees"].GetString();
                        // Sometimes network is sending 0 for fees
                        if (fees == "0") {
                            fees = api::TezosConfigurationDefaults::TEZOS_DEFAULT_FEES;
                        }
                        return std::make_shared<BigInt>(fees);
                    });
        }

        Future<std::shared_ptr<BigInt>>
        NodeTezosLikeBlockchainExplorer::getGasPrice() const {
            throw make_exception(
                api::ErrorCode::RUNTIME_ERROR,
                "getGasPrice is unimplemented for NodeTezosLikeExplorer");
        }

        Future<String>
        NodeTezosLikeBlockchainExplorer::pushLedgerApiTransaction(const std::vector<uint8_t> &transaction) {
            // TODO: TBC with backend team
            std::stringstream body;
            body << "{" << "\"tx\":" << '"' << hex::toString(transaction) << '"' << "}";
            auto bodyString = body.str();
            return _http->POST(fmt::format("blockchain/{}/{}/broadcast_transaction", getExplorerVersion(), getNetworkParameters().Identifier),
                                std::vector<uint8_t>(bodyString.begin(), bodyString.end()))
                    .json().template map<String>(getExplorerContext(), [](const HttpRequest::JsonResult &result) -> String {
                        auto &json = *std::get<1>(result);
                        if (!json.IsString()) {
                            throw make_exception(api::ErrorCode::HTTP_ERROR, "Failed to parse broadcast transaction response, missing transaction hash");
                        }
                        return json.GetString();
                    });
        }

        FuturePtr<TezosLikeBlockchainExplorer::TransactionsBulk>
        NodeTezosLikeBlockchainExplorer::getTransactions(const std::string &address,
                                                         const Either<std::string, uint32_t>& token) const {
            std::string params;
            if (token.isLeft()) {
                params = "&block_hash=" + token.getLeft();
            }
            // TODO FIXME
            auto self = std::make_shared<NodeTezosLikeBlockchainExplorer>(*this); //shared_from_this();
            using EitherTransactionsBulk = Either<Exception, std::shared_ptr<TransactionsBulk>>;
            static std::vector<std::string> txTypes {"Transaction", "Reveal", "Origination", "Delegation"};
            // Note: we should get rid of this if we tweak explorer
            // to have all type of operations at once
            static std::function<FuturePtr<TransactionsBulk> (const std::string address,
                                                              const std::string &params,
                                                              const std::shared_ptr<TransactionsBulk> &txsBulk,
                                                              size_t type)> getTransactionsOfType = [self] (const std::string &address,
                                                                                                            const std::string &parameters,
                                                                                                            const std::shared_ptr<TransactionsBulk> &txsBulk,
                                                                                                            size_t type) -> FuturePtr<TransactionsBulk> {
                return self->_http->GET(fmt::format("blockchain/{}/{}/operations/{}?type={}{}", self->getExplorerVersion(), self->getNetworkParameters().Identifier, address, txTypes[type], parameters))
                        .template json<TransactionsBulk, Exception>(LedgerApiParser<TransactionsBulk, TezosLikeTransactionsBulkParser>())
                        .template flatMapPtr<TransactionsBulk>(self->getExplorerContext(), [=](const EitherTransactionsBulk &result) {
                            if (result.isLeft()) {
                                throw result.getLeft();
                            } else {
                                txsBulk->transactions.insert(txsBulk->transactions.end(), result.getRight()->transactions.begin(), result.getRight()->transactions.end());
                                // Only originated accounts can delegate
                                auto isOriginated = address.find("KT") == 0;
                                if (type == txTypes.size() - 1 || (type == txTypes.size() - 2 && !isOriginated)) {
                                    return FuturePtr<TransactionsBulk>::successful(txsBulk);
                                }
                                return getTransactionsOfType(address, parameters, txsBulk, type + 1);
                            }
                        });
            };
            auto transactionsBulk = std::make_shared<TransactionsBulk>();
            return getTransactionsOfType(address, params, transactionsBulk, 0);
        }

        FuturePtr<Block> NodeTezosLikeBlockchainExplorer::getCurrentBlock() const {
            return _http->GET(fmt::format("blockchain/{}/{}/head", getExplorerVersion(), getNetworkParameters().Identifier))
                    .template json<Block, Exception>(LedgerApiParser<Block, TezosLikeBlockParser>())
                    .template mapPtr<Block>(getExplorerContext(),
                                            [](const Either<Exception, std::shared_ptr<Block>> &result) {
                                                if (result.isLeft()) {
                                                    throw result.getLeft();
                                                } else {
                                                    return result.getRight();
                                                }
                                            });
        }

        std::string NodeTezosLikeBlockchainExplorer::getExplorerVersion() const {
            return _explorerVersion;
        }

        Future<std::shared_ptr<BigInt>> NodeTezosLikeBlockchainExplorer::getEstimatedGasLimit(const std::string &address) const {
            // TODO: activate when backend fix issue with gas limit estimation
            /*
            return getHelper(fmt::format("blockchain/{}/{}/estimate_gas",
                                          getExplorerVersion(),
                                          getNetworkParameters().Identifier),
                              "estimated_gas_limit",
                              std::unordered_map<std::string, std::string>{{"token", address}},
                              api::TezosConfigurationDefaults::TEZOS_DEFAULT_GAS_LIMIT
                );
              */
            return FuturePtr<BigInt>::successful(
                    std::make_shared<BigInt>(api::TezosConfigurationDefaults::TEZOS_DEFAULT_GAS_LIMIT)
            );
        }

        Future<std::shared_ptr<GasLimit>>
        NodeTezosLikeBlockchainExplorer::getEstimatedGasLimit(
            const std::shared_ptr<TezosLikeTransactionApi> &tx) const
        {
            return TezosLikeBlockchainExplorer::getEstimatedGasLimit(_http, getContext(), tx);
        }

        Future<std::shared_ptr<BigInt>> NodeTezosLikeBlockchainExplorer::getStorage(
            const std::string &address) const
        {
            return getHelper(fmt::format("blockchain/{}/{}/estimate_storage",
                                          getExplorerVersion(),
                                          getNetworkParameters().Identifier),
                              "storage",
                              std::unordered_map<std::string, std::string>{{"token", address}},
                              api::TezosConfigurationDefaults::TEZOS_DEFAULT_STORAGE_LIMIT
            );
        }

        Future<std::shared_ptr<BigInt>> NodeTezosLikeBlockchainExplorer::getCounter(const std::string &address) const {
            return getHelper(fmt::format("blockchain/{}/{}/counter",
                                          getExplorerVersion(),
                                          getNetworkParameters().Identifier),
                              "counter",
                              std::unordered_map<std::string, std::string>{{"token", address}}
            );
        }

        Future<std::vector<uint8_t>>
        NodeTezosLikeBlockchainExplorer::forgeKTOperation(const std::shared_ptr<TezosLikeTransactionApi> &tx) const {
            return TezosLikeBlockchainExplorer::forgeKTOperation(tx, getExplorerContext(), _http, getRPCNodeEndpoint());
        }

        Future<std::string>
        NodeTezosLikeBlockchainExplorer::getManagerKey(const std::string &address) const {
            return TezosLikeBlockchainExplorer::getManagerKey(address, getExplorerContext(), _http, getRPCNodeEndpoint());
        }

        Future<bool>
        NodeTezosLikeBlockchainExplorer::isAllocated(const std::string &address) const {
            return TezosLikeBlockchainExplorer::isAllocated(address, getExplorerContext(), _http, getRPCNodeEndpoint());
        }

        Future<std::string>
        NodeTezosLikeBlockchainExplorer::getCurrentDelegate(const std::string &address) const {
            return TezosLikeBlockchainExplorer::getCurrentDelegate(address, getExplorerContext(), _http, getRPCNodeEndpoint());
        }

        Future<bool>
        NodeTezosLikeBlockchainExplorer::isFunded(const std::string &address) const {
            return _http->GET(fmt::format("blockchain/{}/{}/account/{}", address))
                .json(false, true).map<bool>(getExplorerContext(), [=](const HttpRequest::JsonResult &result) {
                    auto& connection = *std::get<0>(result);
                    if (connection.getStatusCode() == 404) {
                        //an empty account
                        return false;
                    }
                    else if (connection.getStatusCode() < 200 || connection.getStatusCode() >= 300) {
                        throw Exception(api::ErrorCode::HTTP_ERROR, connection.getStatusText());
                    }
                    else {
                        auto& json = *std::get<1>(result);

                        // look for the is_funded field
                        const auto field = "is_funded";
                        if (!json.IsObject() || !json.HasMember(field) ||
                            !json[field].IsBool()) {
                            throw make_exception(api::ErrorCode::HTTP_ERROR,
                                                "Failed to get is_funded from network, no (or malformed) field \"result\" in response");
                        }

                        return json[field].GetBool();
                    }
                });
        }

        Future<bool> NodeTezosLikeBlockchainExplorer::isDelegate(const std::string &address) const {
                return _http->GET(fmt::format("blockchain/{}/{}/account/{}",
                                          getExplorerVersion(),
                                          getNetworkParameters().Identifier,
                                          address))
                    .json(false).map<bool>(getExplorerContext(), [=](const HttpRequest::JsonResult &result) {
                        auto& json = *std::get<1>(result);
                        // look for the is_active_delegate field
                        const auto field = "is_active_delegate";
                        if (!json.IsObject() || !json.HasMember(field) ||
                            !json[field].IsBool()) {
                            throw make_exception(api::ErrorCode::HTTP_ERROR,
                                                "Failed to get is_active_delegate from network, no (or malformed) field in response");
                        }
                        return json[field].GetBool();
                    });
        }

        Future<std::shared_ptr<BigInt>>
        NodeTezosLikeBlockchainExplorer::getTokenBalance(const std::string& accountAddress,
                                                        const std::string& tokenAddress) const {
            return Future<std::shared_ptr<BigInt>>::failure(
                Exception(api::ErrorCode::IMPLEMENTATION_IS_MISSING,
                          "Endpoint to get token balance is not implemented."
                ));
        }

        Future<std::shared_ptr<BigInt>> NodeTezosLikeBlockchainExplorer::getHelper(const std::string &url,
                                                                                  const std::string &field,
                                                                                  const std::unordered_map<std::string, std::string> &params,
                                                                                  const std::string &fallbackValue) const {
            bool parseNumbersAsString = true;
            auto networkId = getNetworkParameters().Identifier;

            std::string p, separator = "?";
            for (auto &param : params) {
                p += fmt::format("{}{}={}", separator, param.first, param.second);
                separator = "&";
            }

            return _http->GET(url + p, std::unordered_map<std::string, std::string>())
                    .json(parseNumbersAsString)
                    .mapPtr<BigInt>(getContext(), [field, networkId, fallbackValue] (const HttpRequest::JsonResult& result) {
                        auto& json = *std::get<1>(result);
                        if (!json.IsArray() || json.Size() == 0 || !json[0].IsString()) {
                            throw make_exception(api::ErrorCode::HTTP_ERROR, fmt::format("Failed to get {} for {}", field, networkId));
                        }
                        std::string value = json[0].GetString();
                        if (value == "0" && !fallbackValue.empty()) {
                            value = fallbackValue;
                        }
                        return std::make_shared<BigInt>(value);
            });
        }

    } // namespace core
} // namespace ledger
