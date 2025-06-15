//
// Created by stachoz on 1/5/25.
//

#include "SnmpServerApplication.h"

#include <QApplication>

SnmpServerApplication::SnmpServerApplication(int &argc, char **argv) : QApplication(argc, argv) {
    std::string ip = "172.17.0.1";
    int port = 55555;

    if (argc > 2) {
        ip = argv[1];
        port = std::stoi(argv[2]);
    } else {
        std::cout << "Using default IP and port: " << ip << " " << port << std::endl;
    }

    snmpLogic = std::make_unique<SNMPLogic>(this, ip, port);
}