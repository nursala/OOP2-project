#pragma once
#include "GameObject/GameObject.h"

class MovingObject : public GameObject {
public:
    MovingObject(b2World* world, const b2Vec2& position, const b2Vec2& velocity = b2Vec2_zero);
    ~MovingObject() override;

    b2Vec2 getVelocity() const;
    void setVelocity(const b2Vec2& velocity);

    void update(float deltaTime) override;
};
