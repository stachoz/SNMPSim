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

    void addDevice(Device device) {
        devices.push_back(device);
    }

private:
    void initDevices() {
        Device routerDevice;
        routerDevice.name = "router";
        routerDevice.ip = "127.0.0.1";
        routerDevice.snmpOids = {
            {"cpuUsage", {1, 3, 6, 1, 2, 1}},
            {"memoryUsage", {1, 3, 6, 1, 2, 2}},
            {"networkThroughput", {1, 3, 6, 1, 2, 3}},
            {"interfaceStatus", {1, 3, 6, 1, 2, 4}},
            {"packetLossRate", {1, 3, 6, 1, 2, 5}},
        };

        Device switchDevice;
        switchDevice.name = "switch";
        switchDevice.ip = "127.0.0.1";
        switchDevice.snmpOids = {
            {"cpuUsage", {1, 3, 6, 1, 2, 1}},
            {"memoryUsage", {1, 3, 6, 1, 2, 2}},
            {"packetLossRate", {1, 3, 6, 1, 2, 3}},
            {"networkThroughput", {1, 3, 6, 1, 2, 4}},
            {"portStatus", {1, 3, 6, 1, 2, 5}},
            {"temperature", {1, 3, 6, 1, 2, 6}},
        };

        devices.push_back(switchDevice);
        devices.push_back(routerDevice);
    }

    std::vector<Device> devices;

};
