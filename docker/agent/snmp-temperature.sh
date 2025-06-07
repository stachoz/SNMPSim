#!/bin/bash

generate_random_value() {
    echo $((RANDOM % 31 + 50))
}

generate_spike() {
    echo $((RANDOM % 21 + 61))
}

generate_final_result() {
  chance=$((RANDOM % 10 + 1))

  if [ $chance -eq 1 ]; then
      value=$(generate_spike)
  else
      value=$(generate_random_value)
  fi

  echo $value
}

echo ".1.3.6.1.2025.1"
echo "INTEGER"
echo $(generate_final_result)

