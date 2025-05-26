//
// Created by stachoz on 3/11/25.
//

#pragma once
#include <iostream>
#include <qobject.h>
#include <string>

class DockerContainerLauncher : public QObject {
    Q_OBJECT
public:
    DockerContainerLauncher(const std::string &path, QObject *parent);
    ~DockerContainerLauncher() override;

public slots:
    void startDockerContainer();

private:
    std::vector<std::string> devicesImgNames {};
    std::vector<std::string> containers {};
    std::string execCommand(const char* cmd);
    void loadContainerImageNamesFromFile(const std::string &filename);
};
