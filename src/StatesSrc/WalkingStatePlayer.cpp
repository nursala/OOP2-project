#include "StatesInc/WalkingStatePlayer.h"
#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "StatesInc/AttackingStatePlayer.h"

std::unique_ptr<State> WalkingStatePlayer::handleInput(Character& character) {
    Player& player = static_cast<Player&>(character);


    if (player.getTarget()) {
        return std::make_unique<AttackingStatePlayer>();
    }

    return nullptr;
}
