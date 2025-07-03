#pragma once
#include "CommandInc/Command.h"
#include "Controller.h"

// -----------------------------
// PopScreenCommand - removes the current screen
// -----------------------------
class PopScreenCommand : public Command {
public:
    void execute() override;
};
