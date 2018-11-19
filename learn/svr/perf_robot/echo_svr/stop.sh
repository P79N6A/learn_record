#!/bin/bash
# by orientlu

pid_=$(cat ./echo_svr.pid)

kill -2 $pid_

