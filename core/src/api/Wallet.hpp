// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from wallet.djinni

#ifndef DJINNI_GENERATED_WALLET_HPP
#define DJINNI_GENERATED_WALLET_HPP

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#ifndef LIBCORE_EXPORT
    #if defined(_MSC_VER)
       #include <libcore_export.h>
    #else
       #define LIBCORE_EXPORT
    #endif
#endif

namespace ledger { namespace core { namespace api {

class AccountCallback;
class AccountCreationInfoCallback;
class AccountListCallback;
class BitcoinLikeWallet;
class BlockCallback;
class CosmosLikeWallet;
class DynamicObject;
class ErrorCodeCallback;
class EventBus;
class ExtendedKeyAccountCreationInfoCallback;
class I32Callback;
class Logger;
class Preferences;
class StellarLikeWallet;
enum class WalletType;
struct AccountCreationInfo;
struct Currency;
struct ExtendedKeyAccountCreationInfo;

/** Class representing a wallet. */
class LIBCORE_EXPORT Wallet {
public:
    virtual ~Wallet() {}

    /**
     * Get name of wallet.
     * @return string
     */
    virtual std::string getName() = 0;

    /**
     * Get account with specific index.
     * @param index, 32-bit integer, index of account in wallet
     * @param callback, Callback returning, if getAccount succeed, an Account object with given index
     */
    virtual void getAccount(int32_t index, const std::shared_ptr<AccountCallback> & callback) = 0;

    /**
     * Get number of accounts instanciated under wallet.
     * @param callback, Callback returning, if getAccountCount succeed, a 32-bit integer representing number of accounts
     */
    virtual void getAccountCount(const std::shared_ptr<I32Callback> & callback) = 0;

    /**
     * Get list of accounts instanciated under wallet in a given range.
     * @param offset, 32-bit integer from which we retrieve accounts
     * @param count, 32-bit integer, number of accounts to retrieve
     * @param callback, ListCallback returning, if getAccounts succeed, list of Accounts object
     */
    virtual void getAccounts(int32_t offset, int32_t count, const std::shared_ptr<AccountListCallback> & callback) = 0;

    /**
     * Get index of next account to create.
     * @return callback, Callback returning a 32-bit integer
     */
    virtual void getNextAccountIndex(const std::shared_ptr<I32Callback> & callback) = 0;

    /**
     * Return event bus through which wallet synchronizes it's accounts and interact with blockchain.
     * @return EventBus object
     */
    virtual std::shared_ptr<EventBus> getEventBus() = 0;

    /**
     * Return synchronization status wallet, true if at least one of accounts is synchronizing.
     * @return bool
     */
    virtual bool isSynchronizing() = 0;

    /**
     * Start synchronization of all accounts under wallet.
     * @return EventBus object through which wallet get notified of account's synchronization status
     */
    virtual std::shared_ptr<EventBus> synchronize() = 0;

    /**
     * Get wallet preferences.
     * @return Preferences object
     */
    virtual std::shared_ptr<Preferences> getPreferences() = 0;

    /**
     * Return account's logger which provides all needed (e.g. database) logs.
     * @return Logger Object
     */
    virtual std::shared_ptr<Logger> getLogger() = 0;

    /**
     * Get preferences of specific account.
     * @param index, 32-bit integer, account's index
     * @return Preferences object
     */
    virtual std::shared_ptr<Preferences> getAccountPreferences(int32_t index) = 0;

    /**
     * Convert wallet to a Bitcoin one.
     * @return BitcoinWallet object
     */
    virtual std::shared_ptr<BitcoinLikeWallet> asBitcoinLikeWallet() = 0;

    /**
     * Convert wallet to a Cosmos one.
     * @return CosmosWallet object
     */
    virtual std::shared_ptr<CosmosLikeWallet> asCosmosLikeWallet() = 0;

    /**
     * Get currency of wallet.
     * @return Currency object
     */
    virtual Currency getCurrency() = 0;

    /**
     * Tell whether wallet is a Bitcoin one.
     * @return bool
     */
    virtual bool isInstanceOfBitcoinLikeWallet() = 0;

    /**
     * Tell whether wallet is an Algorand one.
     * @return bool
     */
    virtual bool isInstanceOfAlgorandLikeWallet() = 0;

    /**
     * Tell whether wallet is a Cosmos one.
     * @return bool
     */
    virtual bool isInstanceOfCosmosLikeWallet() = 0;

    /**
     * Tell whether wallet is a Ethereum one.
     * @return bool
     */
    virtual bool isInstanceOfEthereumLikeWallet() = 0;

    /**
     * Tell whether wallet is a Ripple one.
     * @return bool
     */
    virtual bool isInstanceOfRippleLikeWallet() = 0;

    /**
     * Tell whether wallet is a Stellar one.
     * @return bool
     */
    virtual bool isInstanceOfStellarLikeWallet() const = 0;

    /** Cast the instance to StellarLIkeWallet */
    virtual std::shared_ptr<StellarLikeWallet> asStellarLikeWallet() = 0;

    /**
     * Get wallet type.
     * @return WalletType object
     */
    virtual WalletType getWalletType() = 0;

    /**
     * Get last block of blockchain the wallet operates on.
     * @param callback, Callback returning a Block object
     */
    virtual void getLastBlock(const std::shared_ptr<BlockCallback> & callback) = 0;

    /**
     * Return infos about the creation of specific account.
     * @param accountIndex, 32-bit account, index of account in wallet
     * @param callback, Callback returning an AccountCreationInfo
     */
    virtual void getAccountCreationInfo(int32_t accountIndex, const std::shared_ptr<AccountCreationInfoCallback> & callback) = 0;

    /**TODO */
    virtual void getExtendedKeyAccountCreationInfo(int32_t accountIndex, const std::shared_ptr<ExtendedKeyAccountCreationInfoCallback> & callback) = 0;

    /**
     * Return infos about the next created account.
     * @param callback, Callback returning an AccountCreationInfo
     */
    virtual void getNextAccountCreationInfo(const std::shared_ptr<AccountCreationInfoCallback> & callback) = 0;

    /**TODO */
    virtual void getNextExtendedKeyAccountCreationInfo(const std::shared_ptr<ExtendedKeyAccountCreationInfoCallback> & callback) = 0;

    /**
     * Get account from given account creation infos.
     * @param accountCreationInfo, AccountCreationInfo object
     * @param callback, Callback returning an Account object with given creation infos
     */
    virtual void newAccountWithInfo(const AccountCreationInfo & accountCreationInfo, const std::shared_ptr<AccountCallback> & callback) = 0;

    /**TODO */
    virtual void newAccountWithExtendedKeyInfo(const ExtendedKeyAccountCreationInfo & extendedKeyAccountCreationInfo, const std::shared_ptr<AccountCallback> & callback) = 0;

    /**
     * Erase data (in user's DB) relative to wallet since given date.
     * @param date, start date of data deletion
     */
    virtual void eraseDataSince(const std::chrono::system_clock::time_point & date, const std::shared_ptr<ErrorCodeCallback> & callback) = 0;

    /** Return wallet's configuration */
    virtual std::shared_ptr<DynamicObject> getConfiguration() = 0;
};

} } }  // namespace ledger::core::api
#endif //DJINNI_GENERATED_WALLET_HPP
