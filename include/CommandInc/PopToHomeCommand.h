#pragma once
#include "CommandInc/Command.h"
#include "Controller.h"

// -----------------------------
// PopToHomeCommand - removes all screens and goes to home
// -----------------------------
class PopToHomeCommand : public Command {
public:
    void execute() override;
};
