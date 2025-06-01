#pragma once
#include <unordered_map>
#include <memory>
#include <string>

template <typename ResourceType, typename IdentifierType>
class BaseResourceManager {
public:
    bool load(const IdentifierType& id, const std::string& filename);
    ResourceType& get(const IdentifierType& id);

protected:
    std::unordered_map<IdentifierType, std::unique_ptr<ResourceType>> m_resources;
};

template <typename ResourceType, typename IdentifierType>
bool BaseResourceManager<ResourceType, IdentifierType>::load(const IdentifierType& id, const std::string& filename) {
    auto res = std::make_unique<ResourceType>();
    if (!res->loadFromFile(filename))
        return false;
    m_resources[id] = std::move(res);
    return true;
}

template <typename ResourceType, typename IdentifierType>
ResourceType& BaseResourceManager<ResourceType, IdentifierType>::get(const IdentifierType& id) {
    return *m_resources.at(id);
}