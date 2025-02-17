#!/bin/bash

# random number between 10 and 80
generate_random_value() {
    echo $((RANDOM % 71 + 10))
}

# random number between 90 and 100
generate_spike() {
    echo $((RANDOM % 11 + 90))
}

chance=$((RANDOM % 10 + 1))

if [ $chance -eq 1 ]; then 
    value=$(generate_spike)
else 
    value=$(generate_random_value)
fi

echo $value



