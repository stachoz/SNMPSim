//
// Created by stachoz on 3/11/25.
//


#include "DockerContainerLauncher.h"

#include <fstream>
#include <thread>

DockerContainerLauncher::DockerContainerLauncher(const std::string &path, QObject *parent): QObject(parent) {
    loadContainerImageNamesFromFile(path);
}

DockerContainerLauncher::~DockerContainerLauncher() {
    for(const auto& containerHash : containers) {
        std::string cmd = "docker stop " + containerHash;
        system(cmd.c_str());
    }
}

void DockerContainerLauncher::startDockerContainer() {
    std::thread launcherThread([this]() {
        for(const auto& image : devicesImgNames) {
            std::string result = execCommand(("docker run -d " + image).data());
            containers.push_back(result);
            std::cout << result << std::endl;
        }
    });

    launcherThread.join();
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

void DockerContainerLauncher::loadContainerImageNamesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        devicesImgNames.push_back(line);
    }

    file.close();
}
