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
    explicit DockerContainerLauncher(QObject* parent = nullptr);;

    ~DockerContainerLauncher() override;

public slots:
    void startDockerContainer();

private:
    std::string snmpServerImgName = "snmp-server-app:latest";
    std::vector<std::string> devicesImgNames {
           "snmp-agent:latest",
           "snmp-agent:latest",
           "snmp-agent:latest",
           "snmp-agent-server-device:latest",
           "snmp-agent-server-device:latest",
    };

    std::vector<std::string> containers {};
    std::string execCommand(const char* cmd);
    std::mutex containersMutex;
};
