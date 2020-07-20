// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from idl.djinni

#include "AlgorandAccount.hpp"  // my header
#include "AlgorandAssetAmountCallback.hpp"
#include "AlgorandAssetAmountListCallback.hpp"
#include "AlgorandAssetParamsCallback.hpp"
#include "AlgorandAssetParamsListCallback.hpp"
#include "AlgorandOperationType.hpp"
#include "AlgorandTransaction.hpp"
#include "AlgorandTransactionCallback.hpp"
#include "AmountCallback.hpp"
#include "BoolCallback.hpp"
#include "Marshal.hpp"
#include "StringCallback.hpp"
#include "TimePeriod.hpp"

namespace djinni_generated {

AlgorandAccount::AlgorandAccount() : ::djinni::JniInterface<::ledger::core::api::AlgorandAccount, AlgorandAccount>("co/ledger/core/AlgorandAccount$CppProxy") {}

AlgorandAccount::~AlgorandAccount() = default;


CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ledger::core::api::AlgorandAccount>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getSpendableBalance(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_operationType, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getSpendableBalance(::djinni_generated::AlgorandOperationType::toCpp(jniEnv, j_operationType),
                                 ::djinni_generated::AmountCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getAsset(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_assetId, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getAsset(::djinni::String::toCpp(jniEnv, j_assetId),
                      ::djinni_generated::AlgorandAssetParamsCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1hasAsset(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_address, jstring j_assetId, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->hasAsset(::djinni::String::toCpp(jniEnv, j_address),
                      ::djinni::String::toCpp(jniEnv, j_assetId),
                      ::djinni_generated::BoolCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getAssetBalance(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_assetId, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getAssetBalance(::djinni::String::toCpp(jniEnv, j_assetId),
                             ::djinni_generated::AlgorandAssetAmountCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getAssetBalanceHistory(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_assetId, jstring j_start, jstring j_end, jobject j_period, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getAssetBalanceHistory(::djinni::String::toCpp(jniEnv, j_assetId),
                                    ::djinni::String::toCpp(jniEnv, j_start),
                                    ::djinni::String::toCpp(jniEnv, j_end),
                                    ::djinni_generated::TimePeriod::toCpp(jniEnv, j_period),
                                    ::djinni_generated::AlgorandAssetAmountListCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getAssetsBalances(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getAssetsBalances(::djinni_generated::AlgorandAssetAmountListCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getCreatedAssets(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getCreatedAssets(::djinni_generated::AlgorandAssetParamsListCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getPendingRewards(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getPendingRewards(::djinni_generated::AmountCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getTotalRewards(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getTotalRewards(::djinni_generated::AmountCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1getFeeEstimate(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_transaction, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->getFeeEstimate(::djinni_generated::AlgorandTransaction::toCpp(jniEnv, j_transaction),
                            ::djinni_generated::AmountCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jbyteArray JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1buildRawSignedTransaction(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_rawUnsignedTransaction, jbyteArray j_signature)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        auto r = ref->buildRawSignedTransaction(::djinni::Binary::toCpp(jniEnv, j_rawUnsignedTransaction),
                                                ::djinni::Binary::toCpp(jniEnv, j_signature));
        return ::djinni::release(::djinni::Binary::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1broadcastRawTransaction(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jbyteArray j_transaction, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->broadcastRawTransaction(::djinni::Binary::toCpp(jniEnv, j_transaction),
                                     ::djinni_generated::StringCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1broadcastTransaction(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_transaction, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->broadcastTransaction(::djinni_generated::AlgorandTransaction::toCpp(jniEnv, j_transaction),
                                  ::djinni_generated::StringCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandAccount_00024CppProxy_native_1createTransaction(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_callback)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandAccount>(nativeRef);
        ref->createTransaction(::djinni_generated::AlgorandTransactionCallback::toCpp(jniEnv, j_callback));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace djinni_generated
