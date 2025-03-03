cmake_minimum_required(VERSION 3.25)
project(SNMPSim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/qt6")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

add_subdirectory(apps/snmp-server)
add_subdirectory(apps/host-data-receiver)
add_subdirectory(tests)
add_subdirectory(libs/SnmpMessagesBytesOperations)