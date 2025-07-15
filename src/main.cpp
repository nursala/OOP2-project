#include "Controller.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception> 

int main() {
    try {
        srand(static_cast<unsigned int>(time(nullptr)));
        Controller::getInstance().run();
    }
    catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cout << "An unknown error occurred during execution." << std::endl;
        return 1;
    }
    return 0;
}
