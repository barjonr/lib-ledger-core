// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from idl.djinni

#include "AlgorandOperation.hpp"  // my header
#include "AlgorandOperationType.hpp"
#include "AlgorandTransaction.hpp"
#include "Marshal.hpp"

namespace djinni_generated {

AlgorandOperation::AlgorandOperation() : ::djinni::JniInterface<::ledger::core::api::AlgorandOperation, AlgorandOperation>("co/ledger/core/AlgorandOperation$CppProxy") {}

AlgorandOperation::~AlgorandOperation() = default;


CJNIEXPORT void JNICALL Java_co_ledger_core_AlgorandOperation_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ledger::core::api::AlgorandOperation>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_co_ledger_core_AlgorandOperation_00024CppProxy_native_1getTransaction(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandOperation>(nativeRef);
        auto r = ref->getTransaction();
        return ::djinni::release(::djinni_generated::AlgorandTransaction::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jobject JNICALL Java_co_ledger_core_AlgorandOperation_00024CppProxy_native_1getAlgorandOperationType(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandOperation>(nativeRef);
        auto r = ref->getAlgorandOperationType();
        return ::djinni::release(::djinni_generated::AlgorandOperationType::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_co_ledger_core_AlgorandOperation_00024CppProxy_native_1getRewards(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandOperation>(nativeRef);
        auto r = ref->getRewards();
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_co_ledger_core_AlgorandOperation_00024CppProxy_native_1getAssetAmount(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ledger::core::api::AlgorandOperation>(nativeRef);
        auto r = ref->getAssetAmount();
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

}  // namespace djinni_generated
