#pragma once

#include "Controller.h"

class PopScreenCommand : public Command {
public:
    void execute() override {
        Controller::getInstance().popScreen();
    }
};