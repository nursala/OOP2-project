#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "GameObject/Entity.h"
#include <SFML/Window/Keyboard.hpp>
#include <box2d/box2d.h>

MoveInfo KeyboardMoveStrategy::move(Entity& entity, float deltaTime) {
    auto* body = entity.getBody();
    if (!body) return {};

    MoveInfo info;
    info.row = 1;
    info.faceRight = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        body->SetLinearVelocity(b2Vec2(5.f, 0));
        info.row = 2;
        info.faceRight = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        body->SetLinearVelocity(b2Vec2(-5.f, 0));
        info.row = 2;
        info.faceRight = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        body->SetLinearVelocity(b2Vec2(0, -5.f));
        info.row = 2;
        info.faceRight = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        body->SetLinearVelocity(b2Vec2(0, 5.f));
        info.row = 2;
        info.faceRight = false;
    }
    else {
        body->SetLinearVelocity(b2Vec2(0.f, 0));
        info.row = 1;
    }

    return info;
}
