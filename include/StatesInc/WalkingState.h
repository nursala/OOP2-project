#pragma once

#include <StatesInc/State.h>
#include <MoveStrategyAndInfoInc/MoveInfo.h>

template<typename T>
class WalkingState : public State {
public:
    void enter(Character& character) override {};
    void update(Character& character, float dt) override;
    virtual std::unique_ptr<State> handleInput(Character& character) override = 0;
};

template<typename T>
void WalkingState<T>::update(Character& character, float dt) {
    T& specific = static_cast<T&>(character);
    specific.move(dt);
    const MoveInfo& info = specific.getLastMoveInfo();
    specific.getAnimation().update(info.row, 5, dt, info.faceRight);
}
