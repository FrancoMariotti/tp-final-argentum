#!/bin/bash
installDependencies() {
	echo "Installing Dependencies"
	sudo apt-get install cmake
	sudo apt-get install libsdl2-dev
	sudo apt-get install libsdl2-image-dev
	sudo apt-get install libsdl2-ttf-dev
	sudo apt-get install libsdl2-mixer-dev
	sudo apt-get install libjsoncpp-dev
	sudo apt-get install libcppunit-doc libcppunit-dev
	sudo apt-get install libmsgpack-dev
}

installDependencies
exit 0
