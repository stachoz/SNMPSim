//
// Created by stachoz on 4/18/25.
//

#pragma once
#include <QDateTime>
#include <SnmpFrame.pb.h>
#include <unordered_map>
#include <string>
#include <vector>

#include "DeviceParam.h"
#include "gui/widgets/DeviceStatus.h"


class SnmpDataManager {
public:
    bool isNewDevice(std::string_view ip) const;

    void updateData(const SnmpFrame& frame);

    const std::vector<DeviceParam>& getDeviceParamsByIp(std::string_view ip);

    DeviceStatus checkGeneralDeviceStatus(std::string_view ip);

private:
    std::unordered_map<std::string, std::vector<DeviceParam>> deviceParamsMap {};
    std::unordered_map<std::string, QDateTime> deviceUpdateTimeMap {};
};
