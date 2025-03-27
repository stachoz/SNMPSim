//
// Created by stachoz on 3/11/25.
//
#pragma once

#include <QWidget>

#include "src/DockerContainerLauncher.h"

namespace Ui { class SnmpSimWindow; }

class SnmpSimWindow : public QWidget {
    Q_OBJECT

public:
    explicit SnmpSimWindow(QWidget *parent = nullptr);
    ~SnmpSimWindow() override;

private:
    Ui::SnmpSimWindow *ui;
    std::unique_ptr<DockerContainerLauncher> dockerLauncher = std::make_unique<DockerContainerLauncher>();
};
