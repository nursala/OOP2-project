#include "StatesInc/IdleStatePlayer.h"
#include "StatesInc/WalkingStatePlayer.h"
#include <SFML/Window/Keyboard.hpp>
#include "GameObject/Player.h"
#include <iostream>

void IdleStatePlayer::enter(Player& player) 
{
    player.getAnimation().update(1, 5, 0.0f, true); 
}

void IdleStatePlayer::update(Player& player, float deltaTime) {
	player.move(deltaTime);
    const MoveInfo& info = player.getLastMoveInfo();
    player.getAnimation().update(info.row, 5, deltaTime, info.faceRight);
    player.setFacingRight(info.faceRight);
}

std::unique_ptr<State<Player>> IdleStatePlayer::handleInput(Player& player) {
    if (player.getBody()->GetLinearVelocity().Length() > 0.1f) {
        return std::make_unique<WalkingStatePlayer>();
    }
    return nullptr;
}