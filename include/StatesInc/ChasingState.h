#pragma once
#include "StatesInc/State.h"
#include <memory>

class Enemy;
class ChasingState : public State<Enemy> {
public:
    void enter(Enemy& enemy) override {};
    void update(Enemy& enemy, float dt) override;
    std::unique_ptr<State<Enemy>> handleInput(Enemy& enemy) override;
};