#include "Controller.h"
#include <iostream>

int main() {
	srand(static_cast<unsigned int>(time(nullptr))); 
	Controller::getInstance().run();
	return 0;
}
