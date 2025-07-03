#pragma once
#include <box2d/box2d.h>

class World;

class ContactListener : public b2ContactListener {
public:
    ContactListener(World& world);
    void BeginContact(b2Contact* contact) override;
private:
    World& m_world;
};
