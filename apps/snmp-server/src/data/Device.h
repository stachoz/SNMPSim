//
// Created by stachoz on 2/9/25.
//

#pragma once
#include <map>
#include <string>
#include <vector>

class Device {
public:
    Device(std::string_view name, std::string_view ip);

    void addParameter(const std::pair<std::string, std::vector<unsigned int>>& paramNameOid);;

    const std::map<std::string, std::vector<unsigned int>>& getSnmpOids() const;

    const std::string& getIp() const;

    const std::string& getName() const;

    std::string getParamNameByOid(const std::vector<unsigned int>& oid) const;

private:
    std::string name;
    std::string ip;
    std::map<std::string, std::vector<unsigned int>> snmpOids;
};
