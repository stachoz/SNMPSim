//
// Created by stachoz on 3/21/25.
//

#pragma once
#include <string>

struct DeviceParam {
    std::string paramName;
    std::string oid;
    int32_t value;
    bool isValid;
    std::string unit;
};
