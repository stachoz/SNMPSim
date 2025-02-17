#!/bin/bash

while true:
do
  read INPUT_STRING
  case $INPUT_STRING in
    "PING") echo "PONG" ;;
    "get")
      read OID
      if [ "$OID" == ".1.3.6.1.2137.1.1" ]; then
        echo "$OID"
        echo "integer"
        echo "$(( RANDOM % 100 ))"
      else
        echo "NONE"
      fi ;;
    "getnext")
      echo "$OID"
      echo "NONE" ;;
    *)
      echo "ERROR" ;;
  esac
done
