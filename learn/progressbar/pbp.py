#!/usr/bin/env python
# coding=utf-8

import sys
import time

for i in range(100):
    sys.stdout.write('   \r')
    sys.stdout.flush()
    sys.stdout.write('{}%\r'.format(i))
    sys.stdout.flush()
    time.sleep(0.01)
