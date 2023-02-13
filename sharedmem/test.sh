#!/usr/bin/env bash

./consumer&
./producer
pkill consumer
