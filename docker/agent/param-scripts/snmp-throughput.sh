#!/bin/bash

calculate_throughput(){
    local t=$1
    local sine=$(echo "s($t)" | bc -l)
    local abs_sine=$(echo "scale=2; if($sine < 0) -($sine) else $sine" | bc)
    
    local throughput=$(echo "scale=2; 1000 * $abs_sine" | bc)
    echo "$throughput"
}

t=0
while true; do
    throughput=$(calculate_throughput $t)
    echo "Time: $t seconds, Throughput: $throughput Mbps"
    t=$(echo "$t + 1" | bc)
    sleep 1
done
