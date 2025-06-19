#include "StatesInc/WalkingStatePlayer.h"
#include "StatesInc/IdleStatePlayer.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "GameObject/Player.h"
#include <iostream>

std::unique_ptr<State<Player>> WalkingStatePlayer::handleInput(Player& player) {
    if (player.getBody()->GetLinearVelocity().Length() < 0.1f) {
        return std::make_unique<IdleStatePlayer>();
    }
    return nullptr;
}
