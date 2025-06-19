//#pragma once
//
//#include "GameObject/Entity.h"
//
//class World; // Forward declaration to avoid circular dependency
//class Bullet : public Entity {
//public:
//    Bullet(World& world, const sf::Vector2f& position, const sf::Vector2f& direction, float speed);
//
//    void update(float deltaTime) override;
//    //void handleCollision(Entity& other) override;
//    bool shouldDestroy() const;
//
//private:
//    sf::Vector2f m_direction;
//    float m_speed;
//    float m_lifetime = 0.f;
//    const float MAX_LIFETIME = 3.f;
//    bool m_destroy = false;
//
//	sf::CircleShape m_shape; 
//};
