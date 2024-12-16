add_library(snmp STATIC
        SNMPConstants.h
        SNMPLogic.cpp
        SNMPLogic.h
        SNMPMessageBuilder.cpp
        SNMPMessageBuilder.h
        SNMPMessage.h
        SNMPMessageDecoder.cpp
        SNMPMessageDecoder.h
)

target_link_libraries(snmp PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)