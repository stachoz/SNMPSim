FROM debian:12-slim
LABEL authors="stachoz"

RUN apt-get update && \
    apt-get install -y \
    snmp \
    snmpd \
    vim \
    && apt-get clean

COPY snmp-server.conf /etc/snmp/snmp.conf

EXPOSE 161/udp
