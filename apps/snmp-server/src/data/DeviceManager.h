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

    const Device* getDeviceByIp(std::string_view ip) const {
        auto deviceIt = std::find_if(std::begin(devices), std::end(devices),
            [&ip](const Device &device) {
                return device.getIp() == ip;
            }
        );

        if(deviceIt == std::end(devices)) {
           return nullptr;
        }

        return &*deviceIt;
    }

private:
    void initDevices() {
        Device routerDevice("device1", "172.17.0.3");
        routerDevice.addParameter({"temperature", {1, 3, 6, 1, 2025, 1}});

        Device switchDevice("device2", "172.17.0.4");
        switchDevice.addParameter({"cpuUsage", {1, 3, 6, 1, 2025, 2}});

        Device serverDevice("server", "172.17.0.5");
        serverDevice.addParameter({"cpu-temperature", {1, 3, 6, 1, 2025, 1}});
        serverDevice.addParameter({"cpu-usage", {1, 3, 6, 1, 2025, 2}});
        serverDevice.addParameter({"processes", {1, 3, 6, 1, 2025, 3}});
        serverDevice.addParameter({"memory-usage", {1, 3, 6, 1, 2025, 4}});
        serverDevice.addParameter({"eth0-status", {1, 3, 6, 1, 2025, 5}});

        devices.push_back(routerDevice);
        devices.push_back(switchDevice);
        devices.push_back(serverDevice);

    }

    std::vector<Device> devices;

};
