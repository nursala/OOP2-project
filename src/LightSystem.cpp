#include "LightSystem.h"
#include <cmath>
#include <iostream>

LightSystem::LightSystem(sf::Vector2f areaSize)
    : m_playerVision(std::make_shared<VisionLight>(150,45)),
    m_lightingArea(candle::LightingArea::FOG, { 0.f, 0.f }, areaSize),
	m_weaponLight(std::make_shared<WeaponLight>(150, 45)) // Initialize WeaponLight with range and beam angle
{
    m_playerVision->setIntensity(0.5f);
    
    m_radialLight.setRange(25); 
    m_radialLight.setFade(true);
    m_radialLight.setColor(sf::Color::Blue);
    
    m_weaponLight->setRange(100.f);
    m_weaponLight->setFade(true);
    m_weaponLight->setIntensity(1.f);
    m_weaponLight->setColor(sf::Color::Red);

    m_lightingArea.setAreaColor(sf::Color::Black);
    m_lightingArea.setAreaOpacity(0.8);
}

void LightSystem::update(const sf::Vector2f& playerPos, const sf::Vector2f& mouseWorld)
{
    float angle = std::atan2(mouseWorld.y - playerPos.y, mouseWorld.x - playerPos.x) * 180.f / 3.14159265f;
    m_playerVision->update(playerPos, angle);
    m_weaponLight->update(playerPos, angle);
    m_radialLight.setPosition(playerPos);
}



void LightSystem::drawFinalLights(sf::RenderTarget& target) {
    m_lightingArea.clear();
    m_lightingArea.draw(*m_playerVision);
    m_lightingArea.display();
    target.draw(m_lightingArea); // أو Alpha حسب التأثير المراد
}

void LightSystem::drawLights(sf::RenderTarget& target) {
    target.draw(m_radialLight);
    target.draw(*m_weaponLight);
    target.draw(*m_playerVision);
}

std::shared_ptr<VisionLight>& LightSystem::getPlayerVision() {
    return m_playerVision;
}

std::shared_ptr<WeaponLight>& LightSystem::getWeaponLight() {
    return m_weaponLight;
}


void LightSystem::setPosition(const sf::Vector2f& topLeft) {
    m_lightingArea.setPosition(topLeft);
}
void LightSystem::updateCastLight(
    candle::EdgeVector& closeEdges,
    b2World& world)
{

    std::unordered_set<b2Fixture*> m_hitFixtures;

    m_playerVision->castLightCustom(closeEdges.begin(), closeEdges.end(), world, m_hitFixtures);

	m_weaponLight->castLightCustom(closeEdges.begin(), closeEdges.end(), world, m_hitFixtures);
}

