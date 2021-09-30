#!/bin/bash
set -e

#Cmake
rm -rf /src/build
mkdir /src/build
cd /src/build/
DISTRIB=$(lsb_release -rs | cut -f1 -d.)
if [ "$DISTRIB" = "7" ] ; then
    source /opt/rh/devtoolset-9/enable
fi 
conan install .. -s compiler.libcxx=libstdc++11 --build=missing
if [ "$(cat /etc/debian_version)" = "10.10" ] ; then
    CXXFLAGS="-Wall -Wextra" cmake -DWITH_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug -DWITH_PREFIX_LIB=/usr/lib -DWITH_TESTING=On -DUSE_CXX11_ABI=1 ..
else 
    CXXFLAGS="-Wall -Wextra" cmake3 -DWITH_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug -DWITH_PREFIX_LIB=/usr/lib64 -DWITH_TESTING=On -DUSE_CXX11_ABI=1 ..
fi

#Build
make -j9 
make -j9 install

#Test
test/ut-clib --gtest_output=xml:/src/clib-ut.xml




