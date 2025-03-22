FROM debian:12-slim
LABEL authors="stachoz"

RUN apt-get update && \
    apt-get install -y \
    snmp \
    snmpd \
    vim \
    procps \
    && apt-get clean

COPY snmp-temperature.sh /usr/local/bin/snmp/
COPY snmp-cpu-usage.sh /usr/local/bin/snmp/
COPY random-num.sh /usr/local/bin/snmp/
COPY snmp-memory-usage.sh /usr/local/bin/snmp/
COPY snmp-port-status.sh /usr/local/bin/snmp/

RUN chmod +x /usr/local/bin/snmp/snmp-temperature.sh
RUN chmod +x /usr/local/bin/snmp/snmp-cpu-usage.sh
RUN chmod +x /usr/local/bin/snmp/random-num.sh
RUN chmod +x /usr/local/bin/snmp/snmp-memory-usage.sh
RUN chmod +x /usr/local/bin/snmp/snmp-port-status.sh

COPY snmpd-agent.conf /etc/snmp/snmpd.conf

EXPOSE 161/udp

ENTRYPOINT ["snmpd"]
CMD ["-Lo", "-f"]
