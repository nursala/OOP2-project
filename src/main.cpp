#include "Controller.h"
#include <iostream>

int main() {
	try
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		Controller::getInstance().run();
	}
	catch (...)
	{
		std::cerr << "Unknown exception occurred." << std::endl;
		return 1;
	}
	return 0;
}
