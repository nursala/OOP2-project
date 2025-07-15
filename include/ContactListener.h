#pragma once
#include <box2d/box2d.h>
#include <unordered_map>
#include <functional>
#include <utility>
#include "GameObject/Entity.h"

class World;

class ContactListener : public b2ContactListener {
public:
    ContactListener(World& world);
    void BeginContact(b2Contact* contact) override;

private:
    using CollisionHandler = std::function<void(Entity*, Entity*)>;
    using CollisionKey = std::pair<Constants::EntityType, Constants::EntityType>;

    struct CollisionKeyHash {
        std::size_t operator()(const CollisionKey& key) const {
            return std::hash<int>()(static_cast<int>(key.first)) ^ std::hash<int>()(static_cast<int>(key.second));
        }
    };

    std::unordered_map<CollisionKey, CollisionHandler, CollisionKeyHash> m_dispatchMap;
    World& m_world;
};
