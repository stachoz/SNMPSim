//
// Created by stachoz on 3/11/25.
//


#include "DockerContainerLauncher.h"

#include <thread>

DockerContainerLauncher::DockerContainerLauncher(QObject *parent): QObject(parent) {}

DockerContainerLauncher::~DockerContainerLauncher() {
    for(const auto& containerHash : containers) {
        std::string cmd = "docker stop " + containerHash;
        system(cmd.c_str());
    }
}

void DockerContainerLauncher::startDockerContainer() {
    std::string container1 = execCommand(("docker run -d " + snmpServerImgName).data());
    {
        std::lock_guard lock(containersMutex);
        containers.push_back(container1);
    }

    std::cout << container1 << std::endl;

    std::vector<std::thread> threads;

    for(const auto& image : devicesImgNames) {
        threads.emplace_back([this, image]() {
            std::string result = execCommand(("docker run -d " + image).data());
            {
                std::lock_guard lock(containersMutex);
                containers.push_back(result);
            }
            std::cout << result << std::endl;
        });
    }

    for(auto& t : threads) {
        t.join();
    }
}

std::string DockerContainerLauncher::execCommand(const char *cmd) {
    std::array<char, 128> buffer {};
    std::string result;

    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), &pclose);

    if(!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}
