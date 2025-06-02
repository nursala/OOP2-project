#pragma once
#include <Box2D/Box2D.h>
class RayCastClosest : public b2RayCastCallback {
public:
    RayCastClosest();
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;

    bool hit() const;
    b2Vec2 getPoint() const;
    float getFraction() const;
    b2Fixture* getFixture() const; 
    b2Body* getBody() const;       
    void reset();

private:
    bool m_hit;
    float m_fraction;
    b2Vec2 m_point;
    b2Fixture* m_fixture; 
};
