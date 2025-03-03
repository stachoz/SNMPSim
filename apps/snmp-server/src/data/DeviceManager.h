//
// Created by stachoz on 2/9/25.
//
#pragma once

#include <vector>

#include "Device.h"

class DeviceManager {
public:
    DeviceManager() {
        initDevices();
    }

    const std::vector<Device>& getDevices() const {
        return devices;
    }

    void addDevice(const Device &device) {
        devices.push_back(device);
    }

private:
    void initDevices() {
        Device routerDevice;
        routerDevice.name = "device1";
        routerDevice.ip = "172.17.0.3";
        routerDevice.snmpOids = {
            {"temperature", {1, 3, 6, 1, 2025, 1}},
        };

        Device switchDevice;
        switchDevice.name = "device2";
        switchDevice.ip = "172.17.0.4";
        switchDevice.snmpOids = {
            {"cpuUsage", {1, 3, 6, 1, 2025, 2}},
        };

        devices.push_back(switchDevice);
        devices.push_back(routerDevice);
    }

    std::vector<Device> devices;

};
