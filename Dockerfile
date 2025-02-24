FROM debian:12-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-tools-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app/
COPY CMakeLists.txt /app

RUN ls -al

ENV QT_QPA_PLATFORM=offscreen

RUN mkdir -p build && cd build \
    && cmake .. \
    && cmake --build . --target SNMPSim --config Release

CMD ["/app/build/snmp-server/SNMPSim"]