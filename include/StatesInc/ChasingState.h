#pragma once
#include "StatesInc/WalkingState.h"
#include <memory>

class Enemy;
class ChasingState : public WalkingState<Enemy> {
public:
    std::unique_ptr<State<Enemy>> handleInput(Enemy& enemy) override;
};