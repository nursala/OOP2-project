#pragma once
#include "CommandInc/Command.h"
#include "Controller.h"
#include <memory>

// -----------------------------
// PushScreenCommand - pushes a new screen of a specific type
// -----------------------------
template<typename ScreenType>
class PushScreenCommand : public Command {
public:
    void execute() override {
        Controller::getInstance().pushScreen(std::make_unique<ScreenType>());
    }
};
