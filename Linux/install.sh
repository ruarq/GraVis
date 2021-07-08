#!/bin/sh

sudo apt update

# install necessary libs & programs on system
yes | sudo apt install libsfml-dev g++ make

# build the binary files
./premake5 gmake
make config=release

# copy the binary file into Linux folder
cp Bin/Release/Gravity-Visualization Linux/Gravity-Visualization