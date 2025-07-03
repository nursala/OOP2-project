#pragma once

// -----------------------------
// Command - abstract base class for all commands
// -----------------------------
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};
