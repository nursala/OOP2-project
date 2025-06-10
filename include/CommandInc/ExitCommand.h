#pragma once
#include "CommandInc/Command.h"

class ExitCommand : public Command {
public:
    void execute() override {
        std::exit(0);
    };
};