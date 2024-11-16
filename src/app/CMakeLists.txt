add_executable(SNMPSim
        main.cpp
        snmp/SNMPLogic.cpp
        snmp/SNMPLogic.h
)

target_link_libraries(SNMPSim
        PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
