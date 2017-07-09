#!/bin/bash
# by orientlu

# instll for c++
# https://github.com/google/protobuf/blob/master/src/README.md

exit 0

git clone https://github.com/google/protobuf.git
cd ./protobuf

./autogen.sh

./configure

make
make check
sudo make install
sudo ldconfig # refresh shared library cache.
