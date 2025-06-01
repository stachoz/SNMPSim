//
// Created by stachoz on 5/2/25.
//


#include "DeviceManager.h"

DeviceManager::DeviceManager() {
    devices = loadDevices(config);
}

const std::vector<Device> & DeviceManager::getDevices() const {
    return devices;
}

void DeviceManager::addDevice(const Device &device) {
    devices.push_back(device);
}

const Device * DeviceManager::getDeviceByIp(std::string_view ip) const {
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

std::vector<Device> DeviceManager::loadDevices(const std::string &filename) const {
    std::vector<Device> devices;
    YAML::Node config = YAML::LoadFile(filename);

    for (const auto& node : config["devices"]) {
        Device device {
            node["name"].as<std::string>(),
            node["ip"].as<std::string>()
        };

        for (const auto& p : node["params"]) {
            Param param;
            param.name = p["name"].as<std::string>();
            param.oid = parseOid(p["oid"].as<std::string>());

            if(p["unit"]) {
                param.unit = p["unit"].as<std::string>();
            }

            if (p["error_range"]) {
                const auto& er = p["error_range"];
                if (er["greater_than"]) {
                    param.errorRange.greaterThan = er["greater_than"].as<int>();
                }
                if (er["less_than"]) {
                    param.errorRange.lessThan = er["less_than"].as<int>();
                }
            }

            device.addParam(param);
        }

        devices.push_back(device);
    }

    return devices;
}

std::vector<unsigned int> DeviceManager::parseOid(const std::string &oidStr) const {
    std::vector<unsigned int> oid;
    std::stringstream ss(oidStr);
    std::string token;
    while (std::getline(ss, token, '.')) {
        oid.push_back(static_cast<unsigned int>(std::stoul(token)));
    }
    return oid;
}


