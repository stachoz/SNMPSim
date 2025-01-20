//
// Created by stachoz on 11/16/24.
//
#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>
#include <sstream>

struct SNMPMessage {
    uint16_t requestId {};
    std::vector<unsigned int> oid;
    std::string communityString;
    std::optional<std::variant<int32_t, std::string>> value = std::nullopt;

    bool operator==(const SNMPMessage& other) const {
        return requestId == other.requestId
                && oid == other.oid
                && communityString == other.communityString
                && value == other.value;
    }

    std::string getString() const {
        std::stringstream ss;
        ss << "[SNMP Message] " <<
            " request id: " << requestId <<
            " oid:" << oidToString(oid) <<
            " communityString: " << communityString;

        if(value.has_value()) {
            auto v = value.value();
            ss << " value: ";
            if(std::holds_alternative<std::string>(v)) {
                ss << std::get<std::string>(v);
            }
            else {
                ss << std::to_string(std::get<int32_t>(v));
            }
        }

        return ss.str();
    }

    std::string oidToString(const std::vector<unsigned int>& oid) const {
        std::string oidString;

        std::for_each(oid.begin(), oid.end() - 1, [&oidString](const unsigned int& oidValue) {
            oidString += std::to_string(oidValue) + ".";
        });
        oidString += std::to_string(oid.at(oid.size() - 1));

        return oidString;
    }
};
