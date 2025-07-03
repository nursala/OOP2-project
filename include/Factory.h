#pragma once

#include <unordered_map>
#include <functional>
#include <memory>
#include <tuple>
#include <type_traits>
#include <stdexcept>
#include "Constants.h"        
#include "GameObject/Entity.h" 
#include "iostream"

class Factory {
public:
    using CreatorFunc = std::function<std::unique_ptr<Entity>(void*)>;

    static Factory& instance();

    template <typename T, typename... Args>
    void registerType(Constants::EntityType id);

    template <typename T, typename... Args>
    std::unique_ptr<T> createAs(Constants::EntityType id, Args&&... args);

private:
    Factory() = default;
	Factory(const Factory&) = delete;
	Factory& operator=(const Factory&) = delete;

    std::unordered_map<Constants::EntityType, CreatorFunc> m_creators;
};

//-------------------------------------
// Factory Registration 
template <typename T, typename... Args>
void Factory::registerType(Constants::EntityType id) {
    using TupleType = std::tuple<Args...>;  // نحتفظ بالمراجع كما هي

    m_creators[id] = [](void* args) -> std::unique_ptr<Entity> {
        auto* tuple = static_cast<TupleType*>(args);
        return std::apply([](auto&&... unpackedArgs) {
            return std::make_unique<T>(std::forward<decltype(unpackedArgs)>(unpackedArgs)...);
            }, *tuple);
        };
}

//-------------------------------------
// Factory Creation
template <typename T, typename... Args>
std::unique_ptr<T> Factory::createAs(Constants::EntityType id, Args&&... args) 
{
    using TupleType = std::tuple<Args&&...>;

    auto it = m_creators.find(id);
    if (it == m_creators.end())
        throw std::runtime_error("Type not registered in Factory");

    TupleType tuple(std::forward<Args>(args)...);
    std::unique_ptr<Entity> base = it->second(static_cast<void*>(&tuple));
    return std::unique_ptr<T>(static_cast<T*>(base.release()));
}
