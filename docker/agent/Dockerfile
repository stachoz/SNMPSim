FROM debian:12-slim
LABEL authors="stachoz"

COPY debian.sources /etc/apt/sources.list.d/debian.sources

RUN apt-get update && \
    apt-get install -y \
    snmp \
    snmpd \
    snmp-mibs-downloader \
    vim \
    procps \
    && apt-get clean \
    && download-mibs

COPY random-num.sh /usr/local/bin/snmp/
COPY custom_response.sh /usr/local/bin/snmp/
RUN chmod +x /usr/local/bin/snmp/random-num.sh
RUN chmod +x /usr/local/bin/snmp/custom_response.sh

COPY snmpd-agent.conf /etc/snmp/snmpd.conf

EXPOSE 161/udp