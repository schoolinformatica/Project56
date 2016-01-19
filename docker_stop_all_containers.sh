#!/bin/bash

RUNNING=$(docker inspect --format="{{ .State.Running }}" postgres 2> /dev/null)

if [ "$RUNNING" == "true" ]; then
  sudo docker stop postgres
  sudo docker rm postgres
fi

if [ "$RUNNING" == "false" ]; then
  sudo docker rm postgres
fi

RUNNING=$(docker inspect --format="{{ .State.Running }}" webserver 2> /dev/null)

if [ "$RUNNING" == "true" ]; then
  sudo docker stop webserver
  sudo docker rm webserver
fi

if [ "$RUNNING" == "false" ]; then
  sudo docker rm webserver
fi
