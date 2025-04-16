cmake_minimum_required(VERSION 3.25)
project(HostDataReceiver)

add_executable(HostDataReceiver
        src/main.cpp
)

target_sources(HostDataReceiver PRIVATE
        src/DataReceiverApplication.cpp
        src/DataReceiverApplication.h
        src/DockerContainerLauncher.cpp
        src/DockerContainerLauncher.h
        src/DataReceiverLogic.cpp
        src/DataReceiverLogic.h
        src/DeviceParam.h
        gui/windows/SnmpSimWindow.cpp
        gui/windows/SnmpSimWindow.h
        gui/windows/SnmpSimWindow.ui
        gui/widgets/DeviceWidget.cpp
        gui/widgets/DeviceWidget.h
        gui/widgets/LEDWidget.cpp
        gui/widgets/LEDWidget.h
        gui/widgets/DeviceStatus.h
        gui/widgets/DeviceDetailsWidget.cpp
        gui/widgets/DeviceDetailsWidget.h
)

target_link_libraries(HostDataReceiver PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
        Qt6::Gui
        proto
)

target_link_libraries(HostDataReceiver PRIVATE
        SNMPBytesOperationLib
)

target_include_directories(HostDataReceiver PRIVATE ${CMAKE_SOURCE_DIR}/libs/SNMPBytesOperations/src)
target_include_directories(HostDataReceiver PUBLIC ${CMAKE_BINARY_DIR}/proto)
target_include_directories(HostDataReceiver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
