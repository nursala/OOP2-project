#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <stdexcept>
#include "GameObject/Entity.h"
#include "ResourseInc/TextureManager.h"

class Factory {
public:
    using CreatorFunc = std::function<std::unique_ptr<Entity>()>;

    static Factory& instance();

    template <typename T, typename... Args>
    void registerType(TextureID id, Args&&... args);

    template<typename T>
    std::unique_ptr<T> createAs(TextureID id);

private:
    Factory() = default;
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

    std::unordered_map<TextureID, CreatorFunc> m_creators;
};

template <typename T, typename... Args>
void Factory::registerType(TextureID id, Args&&... args) {
    static_assert(std::is_base_of<Entity, T>::value, "T must inherit from Entity");

    auto argsTuple = std::make_tuple(std::forward<Args>(args)...);

    m_creators[id] = [argsTuple = std::move(argsTuple)]() -> std::unique_ptr<Entity> {
        return std::apply([](auto&&... unpackedArgs) {
            return std::make_unique<T>(std::forward<decltype(unpackedArgs)>(unpackedArgs)...);
            }, argsTuple);
        };
}

template<typename T>
std::unique_ptr<T> Factory::createAs(TextureID id) {
    static_assert(std::is_base_of<Entity, T>::value, "T must inherit from Entity");

    auto it = m_creators.find(id);
    if (it != m_creators.end())
        return std::unique_ptr<T>(static_cast<T*>(it->second().release()));

    throw std::runtime_error("Unknown TextureID in createAs");
}
