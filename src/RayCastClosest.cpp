#include "RayCastClosest.h"

//-------------------------------------
//RayCastClosest Ctor
RayCastClosest::RayCastClosest()
    : m_hit(false), m_fraction(1.0f), m_point(0.f, 0.f), m_fixture(nullptr)
{
}

//-------------------------------------
// ReportFixture method
float RayCastClosest::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
    const b2Vec2& normal, const float fraction)
{
    m_hit = true;
    m_point = point;
    m_fraction = fraction;
    m_fixture = fixture; 
    return fraction;
}

//-------------------------------------
// Getters
b2Fixture* RayCastClosest::getFixture() const { return m_fixture; }

//-------------------------------------
b2Body* RayCastClosest::getBody() const { return m_fixture ? m_fixture->GetBody() : nullptr; }

//-------------------------------------
b2Vec2 RayCastClosest::getPoint() const {
    return m_point;
}

//-------------------------------------
float RayCastClosest::getFraction() const {
    return m_fraction;
}

//-------------------------------------
bool RayCastClosest::hit() const {
    return m_hit;
}

//-------------------------------------
// Reset method
void RayCastClosest::reset()
{
    m_hit = false;
    m_fraction = 1.0f;
    m_point.Set(0.f, 0.f);
    m_fixture = nullptr;
}

