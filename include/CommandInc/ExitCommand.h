#pragma once
#include "CommandInc/Command.h"

// -----------------------------
// ExitCommand - exits the application
// -----------------------------
class ExitCommand : public Command {
public:
    void execute() override;
};
