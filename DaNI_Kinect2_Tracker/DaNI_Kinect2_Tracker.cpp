
#include "stdafx.h"
#include <iostream>
#include <sstream>

#include "Kinect2_Tools.h"

int main(int argc, char ** argv) {
	try {
		Kinect kinect;
		kinect.run();
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << std::endl;
	}
}