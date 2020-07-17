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

init() {
	echo "Init installer"

	echo "Hello $USER How are you??"

	read -p "" answer
	
	if [ "$answer" == "ok" ]
	then
		echo "Hi,$USER"
	fi

	exit 1
}

case $1 in
-d)
	installDependencies
	exit 0
;;
-i)
	init
	exit 0
;;
esac

exit 0
