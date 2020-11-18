#!/usr/bin/env bash

ST=$SECONDS

echo Setting up build directory ...
echo 
rm -rf ./build
mkdir ./build

echo Runing cmake commands ...
echo 
cmake . -Bbuild || exit 1
cmake . --build build -DCMAKE_BUILD_TYPE=Debug || exit 2

echo 
echo Runing make commands ...
echo

cd ./build
make -j 16 || exit 3

DURATION=$(($SECONDS - ST))


echo
echo Finished !
echo Time: $DURATION seconds
echo