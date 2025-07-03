#include "CommandInc/ExitCommand.h"
#include <cstdlib>

void ExitCommand::execute() {
    std::exit(0);
}
