#include "CommandInc/PopToHomeCommand.h"
#include "Controller.h"

void PopToHomeCommand::execute() {
    Controller::getInstance().setPopFlagToHome();
}
