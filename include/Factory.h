#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include "ResourseInc/TextureManager.h"
#include "GameObject/Entity.h"
#include "GameObject/Player.h"
#include "LoadMap.h"

class Factory {
public:
    using Creator = std::function<std::unique_ptr<Entity>(b2World&)>;
    using CreatorFuncWithNavigation = std::function<std::unique_ptr<Entity>(b2World&, const LoadMap&, const Player&)>;

    static Factory& instance();

    void registerWithNavigation(TextureID id, CreatorFuncWithNavigation creator);
    std::unique_ptr<Entity> create(TextureID id, b2World& world, const LoadMap& map, const Player& player);

    void registerType(TextureID id, Creator creator);

    std::unique_ptr<Entity> create(TextureID id, b2World& world);


private:
	Factory() = default;
	Factory(const Factory&) = delete;
	Factory& operator=(const Factory&) = delete;
    std::unordered_map<TextureID, Creator> m_creators;
    std::unordered_map<TextureID, CreatorFuncWithNavigation> m_creatorsNav;
};
