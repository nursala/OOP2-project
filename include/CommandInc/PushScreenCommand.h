#pragma once
#include "CommandInc/Command.h"
#include "Controller.h"
#include <memory>

template<typename ScreenType>
class PushScreenCommand : public Command {
public:
    void execute() override {
        Controller::getInstance().pushScreen(std::make_unique<ScreenType>());
    }
};

template<typename ScreenType>
class PopPushScreenCommand : public Command {
public:
    void execute() override {
        Controller::getInstance().setPopFlag();
        Controller::getInstance().pushScreen(std::make_unique<ScreenType>());
    }
};