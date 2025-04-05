//
// Created by stachoz on 3/11/25.
//

#pragma once
#include <iostream>
#include <string>

class DockerContainerLauncher : public QObject {
    Q_OBJECT
public:
    explicit DockerContainerLauncher(QObject* parent = nullptr) : QObject(parent) {};

    ~DockerContainerLauncher() override {
        for(auto& containerHash : containers) {
            std::cout << "Stopping containers" << std::endl;
            std::string cmd = "docker stop " + containerHash;
            system(cmd.c_str());
        }
    };

public slots:
    void startDockerContainer() {
        std::string container1 = execCommand("docker run -d snmp-server-app:latest");
        std::string container2 = execCommand("docker run -d snmp-agent:latest");
        std::string container3 = execCommand("docker run -d snmp-agent:latest");
        std::string container4 = execCommand("docker run -d snmp-agent-server-device:latest");

        containers.push_back(container1);
        containers.push_back(container2);
        containers.push_back(container3);
        containers.push_back(container4);

        for (auto& conHash : containers) {
            std::cout << conHash << std::endl;
        }
    }

private:
    std::vector<std::string> containers {};

    std::string execCommand(const char* cmd) {
        std::array<char, 128> buffer {};
        std::string result;

        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

        if(!pipe) {
            throw std::runtime_error("popen() failed!");
        }

        while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }

        return result;
    }
};
