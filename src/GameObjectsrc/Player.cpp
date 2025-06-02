#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"

Player::Player(b2World& world)
    : Entity(world, TextureManager::instance().get(TextureID::Player), { 350,350 }, {5,5}, 0.4)
{
}

void Player::update(float deltaTime)
{
    int row = 1;
    bool faceRight = true;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_body->SetLinearVelocity(b2Vec2(10.f, m_body->GetLinearVelocity().y));
        row = 2;
        faceRight = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_body->SetLinearVelocity(b2Vec2(-10.f, m_body->GetLinearVelocity().y));
        row = 2;
        faceRight = false;
    }
    else {
        m_body->SetLinearVelocity(b2Vec2(0.f, m_body->GetLinearVelocity().y));
        row = 1;
    }

    b2Vec2 pos = m_body->GetPosition();
    m_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);

    m_animation.update(row, 5, deltaTime, faceRight);
    m_sprite.setTextureRect(m_animation.getUvRect());
}
