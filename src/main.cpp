#include "Controller.h"
#include <Game.h>
#include <ctime>
int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	//Game game;
	Controller controller;
	controller.run();
	//game.run();
}
