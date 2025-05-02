//
// Created by stachoz on 2/9/25.
//
#pragma once

#include <vector>
#include "Device.h"


class DeviceManager {
public:
    DeviceManager();

    const std::vector<Device>& getDevices() const;

    void addDevice(const Device &device);

    const Device* getDeviceByIp(std::string_view ip) const;

private:
    const std::string config = "devices.yaml";
    std::vector<Device> devices;

    std::vector<Device> loadDevices(const std::string& filename) const;

    std::vector<unsigned int> parseOid(const std::string& oidStr) const;
};
