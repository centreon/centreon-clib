#!/bin/bash

pid=$(ps ax | grep "ut-clib" | grep -v grep | awk '{print $1}')

ps -edf | grep "\<$pid\>" | grep -v grep | awk '{print $2, " => ", $8}' | grep -v "$pid"
