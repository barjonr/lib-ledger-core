/*
 *
 * BlockchainSynchronizer.hpp
 * ledger-core
 *
 * Created by Andrii Korol on 19/11/2018.
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Ledger
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
#pragma once

#include <utils/Either.hpp>
#include <events/ProgressNotifier.h>
#include <wallet/NetworkTypes.hpp>
#include <wallet/Explorer.hpp>
#include <wallet/PartialBlockStorage.hpp>

namespace ledger {
    namespace core {

        template<typename NetworkType>
        Future<bool> DownloadBlockTransactions(
            const api::ExecutionContext& executionContext,
            const ExplorerV2<NetworkType>& explorer,
            const PartialBlockStorage<NetworkType>& storage,
            const std::vector<std::string>& addresses,
            const std::string& blockHash)
        {
            return explorer.getTransactions(addresses, blockHash)
                .flatMap<Future<bool>>(executionContext, 
                    [](const std::shared_ptr<typename ExplorerV2<NetworkType>::TransactionBulk>& bulk) -> Future<bool> {
                        ExplorerV2<NetworkType>::TransactionBulk &x = bulk.get();
                        x.second()
                        return 0;
                    });
        }
    }
}
