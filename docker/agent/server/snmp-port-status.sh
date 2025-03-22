#!/bin/bash


chance=$((RANDOM % 10 + 1))

if [ $chance -eq 1 ]; then 
    value=0
else 
    value=1
fi

echo ".1.3.6.1.2025.5"
echo "INTEGER"
echo $value




