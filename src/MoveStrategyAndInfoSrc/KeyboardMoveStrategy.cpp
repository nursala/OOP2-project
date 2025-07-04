#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "GameObject/Character.h"
#include <SFML/Window/Keyboard.hpp>
#include <box2d/box2d.h>
#include "ResourseInc/SoundManger.h"

void KeyboardMoveStrategy::move(Character& character, float deltaTime) {
   
    (void) deltaTime;
    auto* body = character.getBody();
    if (!body) return;
	auto speed = character.getSpeed();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        body->SetLinearVelocity(b2Vec2(speed, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        body->SetLinearVelocity(b2Vec2(-speed, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        body->SetLinearVelocity(b2Vec2(0, -speed));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        body->SetLinearVelocity(b2Vec2(0, speed));
    }
    else {
        body->SetLinearVelocity(b2Vec2(0.f, 0));
    }
}
