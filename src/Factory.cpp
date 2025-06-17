#include "Factory.h"

Factory& Factory::instance() {
    static Factory inst;
    return inst;
}

void Factory::registerType(TextureID id, Creator creator) {
    m_creators[id] = std::move(creator);
}

std::unique_ptr<Entity> Factory::create(TextureID id, b2World& world) {
    auto it = m_creators.find(id);
    if (it != m_creators.end())
        return it->second(world);
    return nullptr;
}
