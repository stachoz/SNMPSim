cmake_minimum_required(VERSION 3.29)
project(SNMPSim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/usr/lib/qt6")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

add_subdirectory(src)
add_subdirectory(tests)