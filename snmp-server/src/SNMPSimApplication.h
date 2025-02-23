//
// Created by stachoz on 1/5/25.
//

#pragma once

#include <QApplication>

#include "SNMPLogic.h"

class SNMPSimApplication : public QApplication{
    Q_OBJECT
public:
    SNMPSimApplication(int &argc, char **argv);

private:
    std::unique_ptr<SNMPLogic> snmpLogic = std::make_unique<SNMPLogic>();
};
