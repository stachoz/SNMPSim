cmake_minimum_required(VERSION 3.25)
project(HostDataReceiver)

add_executable(HostDataReceiver
        src/main.cpp
)

target_sources(HostDataReceiver PRIVATE
        src/DataReceiverApplication.h
)

target_include_directories(HostDataReceiver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(HostDataReceiver PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)