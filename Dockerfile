#  STAGE 1: Build
FROM debian:12-slim as builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-tools-dev \
    protobuf-compiler \
    libprotobuf-dev \
    libyaml-cpp-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

ENV QT_QPA_PLATFORM=offscreen

RUN mkdir build && cd build \
    && cmake .. \
    && cmake --build . --target SNMPServer --config Release

#  STAGE 2: Runtime
FROM debian:12-slim

RUN apt-get update && apt-get install -y \
    qt6-base-dev \
    libprotobuf-dev \
    libyaml-cpp-dev \
    && rm -rf /var/lib/apt/lists/*

ENV QT_QPA_PLATFORM=offscreen

WORKDIR /snmp-server

COPY --from=builder /app/build/apps/snmp-server/SNMPServer ./SNMPServer
COPY --from=builder /app/build/apps/snmp-server/devices.yaml ./devices.yaml

CMD ["./SNMPServer"]