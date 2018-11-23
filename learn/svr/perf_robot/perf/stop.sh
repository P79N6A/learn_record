#!/bin/bash
# by orientlu

pid_=$(cat ./perf.pid)

kill -2 $pid_
