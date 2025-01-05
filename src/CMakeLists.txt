add_library(SnmpSimLib)

target_include_directories(SnmpSimLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(SnmpSimLib PRIVATE
        app/SNMPSimApplication.cpp
        app/SNMPSimApplication.h
        snmp/SNMPLogic.cpp
        snmp/SNMPLogic.h
        snmp/SNMPMessageBuilder.cpp
        snmp/SNMPMessageBuilder.h
        snmp/SNMPMessageDecoder.cpp
        snmp/SNMPMessageDecoder.h
        snmp/data/SNMPConstants.h
        snmp/data/SNMPMessage.h
)

target_link_libraries(SnmpSimLib PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)

add_executable(SNMPSim
        main.cpp
)