#!/usr/bin/env bash


echo Setting up build directory ...
echo 
rm -rf ./build
mkdir ./build

echo Runing cmake commands ...
echo 
cmake . -Bbuild
cmake . --build build

echo 
echo Runing make commands ...
echo

cd ./build
make


echo
echo Finished !