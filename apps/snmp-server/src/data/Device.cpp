//
// Created by stachoz on 3/21/25.
//

#include "Device.h"

Device::Device(std::string_view name, std::string_view ip) {
    this->name = name;
    this->ip = ip;
}

void Device::addParameter(const std::pair<std::string, std::vector<unsigned int>> &paramNameOid) {
    snmpOids.insert(paramNameOid);
}

const std::map<std::string, std::vector<unsigned int>> & Device::getSnmpOids() const {
    return snmpOids;
}

const std::string & Device::getIp() const {
    return ip;
}

const std::string & Device::getName() const {
    return name;
}

std::string Device::getParamNameByOid(const std::vector<unsigned int> &oid) const {
    for(auto& [paramName, paramOid] : snmpOids) {
        if(oid == paramOid) {
            return paramName;
        }
    }
    return "";
}
