#!/bin/sh

#install apt-cyg
lynx -source rawgit.com/transcode-open/apt-cyg/master/apt-cyg > apt-cyg
install apt-cyg /bin

#install necessary packages
echo "########################################################################"
echo "Installing necessary packages..."

apt-cyg install make cmake gcc-g++ autoconf automake libtool libportaudio-devel

echo "All necessary packages installed"
echo "########################################################################"

#make and install TSAL
autoreconf -vi 

./configure --prefix=/usr

make

make install
