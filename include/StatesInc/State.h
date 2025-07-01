#pragma once

#include <memory>

class Character; 
class State {
public:
    virtual ~State() = default;

    // Called every frame to update logic/animation
    virtual void update(Character& character, float deltaTime) = 0;

    // Called to check input and determine state transitions
    virtual std::unique_ptr<State> handleInput(Character& character) = 0;
};
