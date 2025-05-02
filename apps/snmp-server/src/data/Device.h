//
// Created by stachoz on 2/9/25.
//

#pragma once

#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

struct ErrorRange {
    std::optional<int> greaterThan;
    std::optional<int> lessThan;
};

struct Param {
    std::string name;
    std::vector<unsigned int> oid;
    ErrorRange errorRange;
};

class Device {
public:
    Device(std::string_view name, std::string_view ip);
    Device() = default;

    const std::string& getIp() const;

    const std::string& getName() const;

    std::string getParamNameByOid(const std::vector<unsigned int>& oid) const;

    void addParam(const Param& param);

    const std::vector<Param>& getParams() const;

private:
    std::string name;
    std::string ip;
    std::vector<Param> params {};
};
