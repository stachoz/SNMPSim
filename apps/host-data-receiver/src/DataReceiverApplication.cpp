#include "DataReceiverApplication.h"

#include <QPushButton>


DataReceiverApplication::DataReceiverApplication(int &argc, char **argv) : QApplication(argc, argv) {
    connect(logic.get(), &DataReceiverLogic::snmpFrameReceived, window.get(), &SnmpSimWindow::receiveNewSnmpFrame);
    window->show();
}
