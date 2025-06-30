#pragma once
#include "CommandInc/Command.h"
#include "Controller.h"

class PopToHomeCommand : public Command {
public:
    void execute() override {
        Controller::getInstance().setPopFlagToHome();
    }
};