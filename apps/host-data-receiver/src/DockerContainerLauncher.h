//
// Created by stachoz on 3/11/25.
//

#pragma once
#include <string>

class DockerContainerLauncher : public QObject {
    Q_OBJECT
public:
    explicit DockerContainerLauncher(QObject* parent = nullptr) : QObject(parent) {};
public slots:
    void startDockerContainer() {
        system("docker run -d snmp-server-app:latest");
        system("docker run -d snmp-agent:latest");
        system("docker run -d snmp-agent:latest");
        system("docker run -d snmp-agent-server-device:latest");
    }
};
