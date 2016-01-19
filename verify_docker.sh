#!/bin/bash

DOCKER=$(docker -v)

if [ ! "$DOCKER" == "Docker version 1.6.2, build 7c8fca2" ]; then
	exit 42
fi