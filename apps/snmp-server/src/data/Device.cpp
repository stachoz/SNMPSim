//
// Created by stachoz on 3/21/25.
//

#include "Device.h"

Device::Device(std::string_view name, std::string_view ip) {
    this->name = name;
    this->ip = ip;
}

const std::string & Device::getIp() const {
    return ip;
}

const std::string & Device::getName() const {
    return name;
}

std::string Device::getParamNameByOid(const std::vector<unsigned int> &oid) const {
    for(auto& param : params) {
        if(param.oid == oid) {
            return param.name;
        }
    }
    return "";
}

void Device::addParam(const Param &param) {
    params.push_back(param);
}

const std::vector<Param> & Device::getParams() const {
    return params;
}

bool Device::isParamValid(const std::vector<unsigned int> &oid, int32_t value) const {
    auto paramIt = std::find_if(std::begin(params), std::end(params),
        [&](const auto& param) {
        return param.oid == oid;
    });
    if(paramIt == std::end(params)) {
        return false;
    }
    const auto& param = *paramIt;
    if(param.errorRange.greaterThan.has_value()) {
        return !(value > param.errorRange.greaterThan.value());
    }
    if(param.errorRange.lessThan.has_value()) {
        return !(value < param.errorRange.greaterThan.value());
    }
    return true;
}
