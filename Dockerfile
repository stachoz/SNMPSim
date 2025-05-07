FROM debian:12-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    tcpdump \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-tools-dev \
    protobuf-compiler \
    libprotobuf-dev \
    libyaml-cpp-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app/
COPY CMakeLists.txt /app
COPY libs /app

RUN ls -al

ENV QT_QPA_PLATFORM=offscreen

RUN mkdir -p build && cd build \
    && cmake .. \
    && cmake --build . --target SNMPServer --config Release

RUN ls -al /app/build/apps/snmp-server/

WORKDIR /app/build/apps/snmp-server/

CMD ["./SNMPServer"]