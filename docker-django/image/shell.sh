#!/bin/bash

if [ -z $1 ]; then
  echo "shell name"
  exit 1
fi

docker exec -i -t $1 /bin/bash

