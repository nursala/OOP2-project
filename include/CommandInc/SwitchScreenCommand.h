#pragma once
#include "CommandInc/Command.h"
#include "ScreensInc/Screen.h"
#include <functional>

class SwitchScreenCommand : public Command {
public:
    SwitchScreenCommand(std::function<void(ScreenID)> switchFunc,
        ScreenID target) : m_switchFunc(switchFunc), m_target(target) {
    };
    void execute() override {
        m_switchFunc(m_target);
    };

private:
    std::function<void(ScreenID)> m_switchFunc;
    ScreenID m_target;
};