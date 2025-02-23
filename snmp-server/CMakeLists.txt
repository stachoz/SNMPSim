add_library(SnmpSimLib)

target_include_directories(SnmpSimLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(SnmpSimLib PRIVATE
        src/SNMPSimApplication.cpp
        src/SNMPSimApplication.h
        src/SNMPLogic.cpp
        src/SNMPLogic.h
        src/SNMPMessageBuilder.cpp
        src/SNMPMessageBuilder.h
        src/SNMPMessageDecoder.cpp
        src/SNMPMessageDecoder.h
        src/data/SNMPConstants.h
        src/data/SNMPMessage.h
        src/data/Device.h
        src/data/DeviceManager.h
)

target_link_libraries(SnmpSimLib PUBLIC
        Qt6::Core
        Qt6::Widgets
        Qt6::Network
)

add_executable(SNMPSim
        src/main.cpp
)

target_link_libraries(SNMPSim PRIVATE SnmpSimLib
)
