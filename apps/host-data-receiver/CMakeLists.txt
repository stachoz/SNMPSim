cmake_minimum_required(VERSION 3.25)
project(HostDataReceiver)

add_executable(HostDataReceiver
        src/main.cpp
        gui/SnmpSimWindow.cpp
        gui/SnmpSimWindow.h
        gui/SnmpSimWindow.ui
        src/DockerContainerLauncher.cpp
        src/DockerContainerLauncher.h
        src/DataReceiverLogic.cpp
        src/DataReceiverLogic.h
)

target_sources(HostDataReceiver PRIVATE
        src/DataReceiverApplication.cpp
        src/DataReceiverApplication.h
        gui/SnmpSimWindow.cpp
        gui/SnmpSimWindow.h
        gui/SnmpSimWindow.ui
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
        SharedTypesLib
)

target_include_directories(HostDataReceiver PRIVATE ${CMAKE_SOURCE_DIR}/libs/SNMPBytesOperations/src)
target_include_directories(HostDataReceiver PUBLIC ${CMAKE_BINARY_DIR}/proto)
target_include_directories(HostDataReceiver PUBLIC ${CMAKE_BINARY_DIR}/sharedTypes)
target_include_directories(HostDataReceiver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
