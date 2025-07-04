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
		std::cout << "An error occurred during execution." << std::endl;
		return 1;
	}
	return 0;
}
