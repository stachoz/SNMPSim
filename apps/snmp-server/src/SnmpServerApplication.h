//
// Created by stachoz on 1/5/25.
//

#pragma once

#include <QApplication>

#include "SNMPLogic.h"

class SnmpServerApplication : public QApplication{
    Q_OBJECT
public:
    SnmpServerApplication(int &argc, char **argv);
    std::unique_ptr<SNMPLogic> snmpLogic;
};
