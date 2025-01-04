add_executable(SNMPSimApp
        main.cpp
)


target_link_libraries(SNMPSimApp PRIVATE
        Qt6::Widgets
        Qt6::Core
        snmp
)