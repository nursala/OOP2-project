#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <memory>
#include "Constants.h"

template <typename ResourceType, typename IdentifierType>
class BaseResourceManager 
{                                                                           
public:
    bool load(const IdentifierType& id, const std::string& filename);
	virtual ~BaseResourceManager() = default;
    const ResourceType* get(const IdentifierType& id) const;

	static const sf::Font& getDefaultFont() {
		static sf::Font defaultFont;
		if (!defaultFont.loadFromFile("myFont.otf")) {
			throw std::runtime_error("Failed to load default font");
		}
		return defaultFont;
	}
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
const ResourceType* BaseResourceManager<ResourceType, IdentifierType>::get(const IdentifierType& id) const 
{
    auto it = m_resources.find(id);
    if (it != m_resources.end())
        return it->second.get();
    return nullptr;
}


