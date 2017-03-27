// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from http_client.djinni

#pragma once

#include <functional>
#include <iostream>
#include <string>

namespace ledger { namespace core { namespace api {

enum class HttpMethod : int {
    GET,
    POST,
    PUT,
    DEL,
};
std::string to_string(const HttpMethod& httpMethod);
std::ostream &operator<<(std::ostream &os, const HttpMethod &o);

} } }  // namespace ledger::core::api

namespace std {

template <>
struct hash<::ledger::core::api::HttpMethod> {
    size_t operator()(::ledger::core::api::HttpMethod type) const {
        return std::hash<int>()(static_cast<int>(type));
    }
};

}  // namespace std