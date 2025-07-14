#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "Constants.h"

// Base class for resource management using identifier and file path
template <typename ResourceType, typename IdentifierType>
class BaseResourceManager
{
public:
    virtual ~BaseResourceManager() = default;

    // Loads the resource from file and stores it with the given ID
    bool load(const IdentifierType& id, const std::string& filename);


    // Retrieves a pointer to the resource for a given ID
    const ResourceType* get(const IdentifierType& id) const;
protected:
    std::unordered_map<IdentifierType, std::unique_ptr<ResourceType>> m_resources;  // Map of loaded resources
};

// Template implementation: Load a resource from file
template <typename ResourceType, typename IdentifierType>
bool BaseResourceManager<ResourceType, IdentifierType>::load(const IdentifierType& id, const std::string& filename) {
    auto res = std::make_unique<ResourceType>();
    if (!res->loadFromFile(filename))

        return false;
    m_resources[id] = std::move(res);
    return true;
}

// Template implementation: Get a resource by ID
template <typename ResourceType, typename IdentifierType>
const ResourceType* BaseResourceManager<ResourceType, IdentifierType>::get(const IdentifierType& id) const {
    auto it = m_resources.find(id);
    if (it != m_resources.end())
        return it->second.get();
    return nullptr;
}
