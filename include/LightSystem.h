#pragma once

#include <SFML/Graphics.hpp>
#include "VisionLight.h"
#include "WeaponLight.h"
#include "Candle/LightingArea.hpp"
#include <Box2D/Box2D.h>

class LightSystem {
public:
	LightSystem(sf::Vector2f areaSize);

	void update(const sf::Vector2f& playerPos, const sf::Vector2f& mouseWorld);


	void drawFinalLights(sf::RenderTarget& target);

	void drawLights(sf::RenderTarget& target);

	std::shared_ptr<VisionLight>& getPlayerVision();
	std::shared_ptr<WeaponLight>& getWeaponLight();


	void setPosition(const sf::Vector2f& topLeft);

	void updateCastLight( candle::EdgeVector& closeEdges, b2World& world);


private:
	std::shared_ptr<VisionLight> m_playerVision;
	std::shared_ptr<WeaponLight> m_weaponLight;
	candle::RadialLight m_radialLight;
	candle::LightingArea m_lightingArea;
};
