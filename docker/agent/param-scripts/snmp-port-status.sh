#!/bin/bash


chance=$((RANDOM % 10 + 1))

if [ $chance -eq 1 ]; then 
    value=0
else 
    value=1
fi

echo $value



