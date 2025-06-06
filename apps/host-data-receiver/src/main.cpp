#include "DataReceiverApplication.h"
#include <csignal>

int main(int argc, char *argv[]) {
    std::signal(SIGTERM, []([[maybe_unused]]int sig) {
        std::cout << "Received SIGTERM" << std::endl;
        QApplication::quit();
    });
    DataReceiverApplication app(argc, argv);
    app.exec();
}
