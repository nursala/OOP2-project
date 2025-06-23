#pragma once
#include <box2d/box2d.h>
class World; // ?? forward declaration

class ContactListener : public b2ContactListener {
public:
    ContactListener(World& world); // ?? constructor with World reference
    void BeginContact(b2Contact* contact) override;
private:
    World& m_world; // ?? store reference to world
};
