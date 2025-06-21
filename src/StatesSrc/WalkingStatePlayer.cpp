#include "StatesInc/WalkingStatePlayer.h"
#include "StatesInc/IdleStatePlayer.h"
#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

std::unique_ptr<State> WalkingStatePlayer::handleInput(Character& character) {
    Player& player = static_cast<Player&>(character);

    if (player.getBody()->GetLinearVelocity().Length() < 0.1f) {
        return std::make_unique<IdleStatePlayer>();
    }
    return nullptr;
}
