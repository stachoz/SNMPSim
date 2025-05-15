//
// Created by stachoz on 4/18/25.
//

#pragma once
#include <unordered_map>
#include <string>
#include <vector>

#include "DeviceParam.h"
#include "gui/widgets/DeviceStatus.h"


class SnmpDataManager {
public:
    bool isNewDevice(std::string_view ip) const {
        return !deviceParamsMap.contains(ip.data());
    }

    void updateData(const SnmpFrame& frame) {
        DeviceParam newDeviceParam {frame.devicename(), frame.oid(), frame.value(), frame.isvalid()};
        auto deviceParamIt = deviceParamsMap.find(frame.ip());
        if(deviceParamIt != deviceParamsMap.end()) {
            auto &params = deviceParamIt->second;
            auto paramByOid = std::find_if(std::begin(params), std::end(params), [this, &frame](const DeviceParam& deviceParam){
                return deviceParam.oid == frame.oid();
            });
            if(paramByOid != params.end()) {
                paramByOid->value = frame.value();
                paramByOid->isValid = frame.isvalid();
            }
            else {
                params.push_back(newDeviceParam);
            }
        }
        else {
            deviceParamsMap[frame.ip()] = {newDeviceParam};
        }
    }

    const std::vector<DeviceParam>& getDeviceParamsByIp(std::string_view ip) {
       return deviceParamsMap[ip.data()];
    }

    DeviceStatus checkGeneralDeviceStatus(std::string_view ip) {
        auto params = deviceParamsMap[ip.data()];
        for(const auto& param : params) {
            if(!param.isValid) {
                return DeviceStatus::DANGER;
            }
        }

        return DeviceStatus::GOOD;
    }

private:
    std::unordered_map<std::string, std::vector<DeviceParam>> deviceParamsMap {};
};
