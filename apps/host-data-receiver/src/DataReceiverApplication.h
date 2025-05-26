//
// Created by stachoz on 2/25/25.
//

#pragma once
#include <QApplication>
#include <SnmpFrame.pb.h>

#include "DataReceiverLogic.h"
#include "gui/windows/SnmpSimWindow.h"


class DataReceiverApplication : public QApplication {
    Q_OBJECT
public:
    DataReceiverApplication(int &argc, char **argv);

private:
    std::unique_ptr<SnmpSimWindow> window;
    std::unique_ptr<DataReceiverLogic> logic = std::make_unique<DataReceiverLogic>();
};
