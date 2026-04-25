# SNMPSim

SNMPSim is a C++ project that provides SNMP server and host data receiver capabilities.

## Architecture

The project functionalities are divided into two main applications:
* **SnmpServer**: An implementation of an SNMP protocol server that periodically sends queries to monitored devices.
* **HostDataReceiver**: An application designed to present the information gathered from monitored devices in a Graphical User Interface (GUI).

This separation is key for flexible deployment across various environments. In a typical test setup, the `HostDataReceiver` runs on the host network, while the `SnmpServer` and simulated device containers run inside a Docker Bridge Network to isolate ports and IPs.

For production deployment, running `SnmpServer` as an independent component allows flexibility—it can run on the same machine as the GUI or on a separate, high-performance server. The `SnmpServer` allows configuration of the IP address and port for the data-receiving application to ensure proper communication.

## Data Flow

The communication flow starts with `SnmpServer` reading its configuration and sending periodic SNMP queries to monitored devices via UDP. When a response is received, the data is processed and packaged into a `SnmpFrame` structure defined using Protocol Buffers.

The `SnmpFrame` contains:
* Data from the SNMP `GET RESPONSE` frame.
* IP address and device name.
* Timestamp of the received response.
* Parameter validation status.
* Value unit.

This structured data is then sent to the `HostDataReceiver`, which updates its GUI accordingly. All inter-component communication leverages UDP (User Datagram Protocol) to ensure fast data transmission.

## Project Structure

* **apps/**
  * `snmp-server` - The main SNMP server application.
  * `host-data-receiver` - Application for receiving host data (GUI).
* **libs/**
  * `SnmpMessagesBytesOperations` - Library for handling SNMP message byte operations.
  * `proto` - Protobuf definitions and generated code.
* **tests/** - Contains the unit test suite for the project (using Google Test).
* **docker/** - Docker configuration and scripts for containerizing the applications and simulating devices.

## Device Simulator Containers

To simulate physical devices, Docker containers run the `snmpd` service (an SNMP agent). These simulators process requests received from the server. They allow defining custom Object Identifiers (OIDs) and scripts that determine how responses are generated.

The device simulator image is based on Debian 12 slim. It comes pre-installed with `snmpd` and includes scripts to simulate various metrics like CPU usage, memory usage, temperature, and port status. Access is strictly controlled via `snmpd.conf`, and custom OIDs in the `.1.3.6.1.2025` tree are mapped to these simulator scripts using the `pass` directive.

## Dependencies

The implementation leverages C++20 and several open-source dependencies:
* **Docker Engine**: Used for running containers.
* **Qt6 Core**: Basic Qt library providing inter-object communication and lifecycle management.
* **Qt6 Network**: Used for handling UDP network communication.
* **Qt6 Widgets**: Provides Graphical User Interface components like buttons and windows.
* **Protocol Buffers (Protobuf)**: A Google library for data serialization. Used for inter-component communication.
* **yaml-cpp**: Enables loading network device configurations from YAML files.
* **Google Test**: Used for writing unit tests.

The build system is CMake (minimum version 3.25).

## Build Instructions

1. Ensure all dependencies are installed.
2. Create a build directory and run CMake:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

## Docker

A `Dockerfile` is provided in the project root to easily build and run the applications in an isolated container environment.
