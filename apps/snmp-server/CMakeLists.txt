cmake_minimum_required(VERSION 3.25)
project(SNMPServer)

add_executable(SNMPServer
        src/main.cpp
)

target_sources(SNMPServer PRIVATE
        src/SnmpServerApplication.cpp
        src/SnmpServerApplication.h
        src/SNMPLogic.cpp
        src/SNMPLogic.h
        src/data/DeviceManager.cpp
        src/data/DeviceManager.h
        src/data/Device.h
        src/data/Device.cpp
)

target_link_libraries(SNMPServer PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
        proto
        SNMPBytesOperationLib
        yaml-cpp
)

target_include_directories(SNMPServer PRIVATE ${CMAKE_SOURCE_DIR}/libs/SNMPBytesOperations/src)
target_include_directories(SNMPServer PUBLIC ${CMAKE_BINARY_DIR}/proto)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/resources/devices.yaml"
               "${CMAKE_CURRENT_BINARY_DIR}/devices.yaml" COPYONLY
)
