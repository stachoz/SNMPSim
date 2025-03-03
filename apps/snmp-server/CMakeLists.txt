cmake_minimum_required(VERSION 3.25)
project(SNMPServer)

add_executable(SNMPServer
        src/main.cpp
)

target_sources(SNMPServer PRIVATE
        src/SNMPSimApplication.cpp
        src/SNMPSimApplication.h
        src/SNMPLogic.cpp
        src/SNMPLogic.h
        src/data/Device.h
        src/data/DeviceManager.h
)

target_link_libraries(SNMPServer PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)

target_link_libraries(SNMPServer PRIVATE
        SNMPBytesOperationLib
)

target_include_directories(SNMPServer PRIVATE ${CMAKE_SOURCE_DIR}/libs/SNMPBytesOperations/src)
