#include "Factory.h"

Factory& Factory::instance() {
    static Factory inst;
    return inst;
}

void Factory::registerWithNavigation(TextureID id, CreatorFuncWithNavigation creator)
{
    m_creatorsNav[id] = std::move(creator);
}

void Factory::registerType(TextureID id, Creator creator) {
    m_creators[id] = std::move(creator);
}

std::unique_ptr<Entity> Factory::create(TextureID id, b2World& world) {
    auto it = m_creators.find(id);
    if (it != m_creators.end())
        return it->second(world);
    throw std::runtime_error("Unknown entity type (bas)");
}

std::unique_ptr<Entity> Factory::create(TextureID id, b2World& world, const LoadMap& map, const Player& player) {
    auto it = m_creatorsNav.find(id);
    if (it != m_creatorsNav.end()) {
        return it->second(world, map, player);
    }
    throw std::runtime_error("Unknown entity type (nav)");
}