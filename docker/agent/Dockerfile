FROM debian:12-slim
LABEL authors="stachoz"

#COPY debian.sources /etc/apt/sources.list.d/debian.sources

RUN apt-get update && \
    apt-get install -y \
    snmp \
    snmpd \
    vim \
    procps \
    && apt-get clean

COPY snmp-temperature.sh /usr/local/bin/snmp/
COPY snmp-cpu-usage.sh /usr/local/bin/snmp/

RUN chmod +x /usr/local/bin/snmp/snmp-temperature.sh
RUN chmod +x /usr/local/bin/snmp/snmp-cpu-usage.sh

COPY snmpd-agent.conf /etc/snmp/snmpd.conf

EXPOSE 161/udp