#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include "ResourseInc/TextureManager.h"
#include "GameObject/Entity.h"

class Factory {
public:
    using Creator = std::function<std::unique_ptr<Entity>(b2World&)>;

    static Factory& instance();

    void registerType(TextureID id, Creator creator);
    std::unique_ptr<Entity> create(TextureID id, b2World& world);

private:
    std::unordered_map<TextureID, Creator> m_creators;
};
