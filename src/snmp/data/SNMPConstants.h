//
// Created by stachoz on 11/16/24.
//

#pragma once
#include <cstdint>

namespace SNMP {
    constexpr uint8_t INTEGER_TYPE {0x02};
    constexpr uint8_t OCTET_STRING_TYPE {0x04};
    constexpr uint8_t NULL_TYPE {0x05};
    constexpr uint8_t OID_TYPE {0x06};
    constexpr uint8_t SEQUENCE_TYPE {0x30};
    constexpr uint8_t GET_REQUEST_TYPE {0xA0};
    constexpr uint8_t RESPONSE_TYPE {0xA2};
    constexpr uint8_t SET_REQUEST_TYPE {0xA3};
    constexpr uint8_t OID_BEGINNING {0x2B};
    constexpr uint8_t VALUE_BITS_MASK {0x7F};    // 01111111
    constexpr uint8_t FIRST_BIT_SET_MASK {0x80}; // 10000000
    constexpr uint8_t VALUE_BITS_NUM {0x07};
    constexpr uint8_t FIRST_BIT_ONE {0x80};
    constexpr uint8_t SNMP_V2 {0x00};
}
