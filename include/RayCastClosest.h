#pragma once

#include <box2d/box2d.h>

class RayCastClosest : public b2RayCastCallback {
public:
    RayCastClosest();

    float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
        const b2Vec2& normal, const float fraction) override;

    b2Fixture* getFixture() const;
    b2Body* getBody() const;
    b2Vec2 getPoint() const;
    float getFraction() const;
    bool hit() const;

    void reset();

private:
    bool m_hit;
    float m_fraction;
    b2Vec2 m_point;
    b2Fixture* m_fixture;
};
