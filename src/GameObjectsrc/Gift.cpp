#include "GameObject/Gift.h"
#include "GameObject/Player.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "WorldInc/World.h"
#include <cmath>
#include <iostream>

namespace {
    // Register the Gift with the factory
    bool registered = [] {
        Factory::instance().registerType<Gift, World&, const b2Vec2&>(
            Constants::EntityType::Gift
        );
        return true;
        }();
}

//---------------------------------------------
// Constructor: sets up sprite, light, and body
//---------------------------------------------
Gift::Gift(World& world, const b2Vec2& position)
    : Entity(world, position), m_type(genrateType())
{
    m_entityType = Constants::EntityType::Gift;
    auto textureID = Constants::GiftTextures[m_type];

    // Set sprite texture
    if (TextureManager::instance().get(textureID))
    {
        m_sprite.setTexture(*TextureManager::instance().get(textureID));
        m_sprite.setTextureRect(sf::IntRect(
            0, 0,
            TextureManager::instance().get(textureID)->getSize().x,
            TextureManager::instance().get(textureID)->getSize().y));
    }

    // Initialize physics body
    init(b2_staticBody, 0.6f);

    // Set up glowing light
    m_radialLight.setRange(50.f);
    m_radialLight.setFade(true);
}

//---------------------------------------------
// Return the type of this gift
//---------------------------------------------
Constants::GiftType Gift::getType() const {
    return m_type;
}

//---------------------------------------------
// Update light pulse effect over time
//---------------------------------------------
void Gift::update(const float dt)
{
    m_pulseTime += dt;

    m_radialLight.setPosition(getPosition());
    m_radialLight.setColor(sf::Color::Green);

    float pulse = std::sin(m_pulseTime * 2.f);
    float intensity = 0.3f + 0.2f * pulse;
    float range = 50.f + 20.f * pulse;

    m_radialLight.setIntensity(intensity);
    m_radialLight.setRange(range);
}

//---------------------------------------------
// Render the light and sprite of the gift
//---------------------------------------------
void Gift::render(RenderLayers& renderLayers) {
    renderLayers.drawLight(m_radialLight);
    renderLayers.drawForeground(m_radialLight);
    renderLayers.drawForeground(m_sprite);
}

//---------------------------------------------
// Customize fixture to act as a sensor
//---------------------------------------------
void Gift::customizeFixtureDef(b2FixtureDef& fixtureDef)
{
    fixtureDef.isSensor = true;
}

//---------------------------------------------
// Hide and mark gift as destroyed
//---------------------------------------------
void Gift::des()
{
    m_visable = false;
    setDestroyed(true);
}

//==================================================
// Double Dispatch Handlers
//==================================================
void Gift::onCollide(Entity& other)
{
    other.onCollideWith(*this);
}

void Gift::onCollideWith(Player& player)
{
   des();
}

Constants::GiftType Gift::genrateType() {
    Constants::GiftType type;

    int chance = rand() % 100;
    if (chance < 30) {
        type = Constants::GiftType::ARMOR;
    }
    else if (chance < 60) {
        type = Constants::GiftType::HEALTH;
    }

    else {
        std::vector<Constants::GiftType> otherTypes;

        const int giftTypeCount = static_cast<int>(Constants::GiftType::SIZE);
        for (int i = 0; i < giftTypeCount; ++i) {
            auto gift = static_cast<Constants::GiftType>(i);
            if (gift != Constants::GiftType::ARMOR && gift != Constants::GiftType::HEALTH) {
                otherTypes.push_back(gift);
            }
        }

        if (!otherTypes.empty()) {
            type = otherTypes[rand() % otherTypes.size()];
        }
        else {
            type = Constants::GiftType::ARMOR;
        }
    }
    return type;
}