#pragma once

#include <memory>

// Templated State base class to be shared between Player, Enemy, etc.
template <typename T>
class State {
public:
    virtual ~State() = default;

    // Called when entering the state
    virtual void enter(T& object) = 0;

    // Called every frame to update logic/animation
    virtual void update(T& object, float deltaTime) = 0;

    // Called to check input and determine state transitions
    virtual std::unique_ptr<State<T>> handleInput(T& object) = 0;
};
