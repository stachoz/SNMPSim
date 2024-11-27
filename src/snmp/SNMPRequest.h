//
// Created by stachoz on 11/16/24.
//

#include <cstdint>
#include <vector>

struct SNMPRequest {
    uint16_t requestId {};
    std::vector<unsigned int> oid;
    std::string communityString;
    std::optional<uint8_t> value = std::nullopt;
};
