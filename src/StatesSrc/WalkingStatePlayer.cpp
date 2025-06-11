#include "StatesInc/WalkingStatePlayer.h"
#include "StatesInc/IdleStatePlayer.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "GameObject/Player.h"
#include <iostream>

void WalkingStatePlayer::enter(Player& player) {
}

void WalkingStatePlayer::update(Player& player, float deltaTime) {
    const MoveInfo& info = player.getLastMoveInfo();
    player.getAnimation().update(info.row, 5, deltaTime, info.faceRight);
    player.setFacingRight(info.faceRight);
}

std::unique_ptr<State<Player>> WalkingStatePlayer::handleInput(Player& player) {
    if (player.getBody()->GetLinearVelocity().Length() < 0.1f) {
        return std::make_unique<IdleStatePlayer>();
    }
    return nullptr;
}
