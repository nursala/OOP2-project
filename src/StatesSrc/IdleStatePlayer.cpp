#include "StatesInc/IdleStatePlayer.h"
#include "StatesInc/WalkingStatePlayer.h"
#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

void IdleStatePlayer::enter(Character& character) {
    Player& player = static_cast<Player&>(character);
}

void IdleStatePlayer::update(Character& character, float deltaTime) {
    Player& player = static_cast<Player&>(character);
    player.move(deltaTime);
    const MoveInfo& info = player.getLastMoveInfo();
    player.getAnimation().update(info.row, 5, deltaTime, info.faceRight);
    player.setFacingRight(info.faceRight);
}

std::unique_ptr<State> IdleStatePlayer::handleInput(Character& character) {
    Player& player = static_cast<Player&>(character);
    if (player.getBody()->GetLinearVelocity().Length() > 0.1f) {
        return std::make_unique<WalkingStatePlayer>();
    }
    return nullptr;
}
