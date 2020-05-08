#!/usr/bin/env bash


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
make || exit 3


echo
echo Finished !