//
// Created by stachoz on 2/9/25.
//

#pragma once
#include <map>
#include <string>
#include <vector>

class Device {
public:
    std::string name;
    std::string ip;
    std::map<std::string, std::vector<unsigned int>> snmpOids;
};

