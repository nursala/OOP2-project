#include "CommandInc/PopScreenCommand.h"
#include "Controller.h"

void PopScreenCommand::execute() {
    Controller::getInstance().setPopFlag();
}
