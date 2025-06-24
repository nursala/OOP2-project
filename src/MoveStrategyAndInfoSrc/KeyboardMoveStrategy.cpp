#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "GameObject/Character.h"
#include <SFML/Window/Keyboard.hpp>
#include <box2d/box2d.h>

MoveInfo KeyboardMoveStrategy::move(Character& character, float deltaTime) {
    auto* body = character.getBody();
    if (!body) return {};

    MoveInfo info;
    info.row = 1;
    info.faceRight = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        body->SetLinearVelocity(b2Vec2(10.f, 0));
        info.row = 2;
        info.faceRight = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        body->SetLinearVelocity(b2Vec2(-10.f, 0));
        info.row = 2;
        info.faceRight = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        body->SetLinearVelocity(b2Vec2(0, -10.f));
        info.row = 2;
        info.faceRight = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        body->SetLinearVelocity(b2Vec2(0, 10.f));
        info.row = 2;
        info.faceRight = false;
    }
    else {
        body->SetLinearVelocity(b2Vec2(0.f, 0));
        info.row = 1;
    }

    return info;
}
