//
// Created by stachoz on 2/25/25.
//

#pragma once
#include <QApplication>
#include <SnmpFrame.pb.h>

#include <gui/SnmpSimWindow.h>

#include "DataReceiverLogic.h"


class DataReceiverApplication : public QApplication {
    Q_OBJECT
public:
    DataReceiverApplication(int &argc, char **argv);

private:
    std::unique_ptr<SnmpSimWindow> window = std::make_unique<SnmpSimWindow>();
    std::unique_ptr<DataReceiverLogic> logic = std::make_unique<DataReceiverLogic>();
};
