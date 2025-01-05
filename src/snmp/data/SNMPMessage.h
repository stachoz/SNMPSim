//
// Created by stachoz on 11/16/24.
//
#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

struct SNMPMessage {
    uint16_t requestId {};
    std::vector<unsigned int> oid;
    std::string communityString;
    std::optional<int32_t> value = std::nullopt;

    bool operator==(const SNMPMessage& other) const {
        return requestId == other.requestId
                && oid == other.oid
                && communityString == other.communityString
                && value == other.value;
    }
};


