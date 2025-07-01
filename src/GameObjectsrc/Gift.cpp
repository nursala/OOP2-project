#include "GameObject/Gift.h"
#include "GameObject/Player.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "WorldInc/World.h"
#include <iostream> 
#include "Constants.h"

Gift::Gift(World& world , b2Vec2& position  , Constants::TextureID type) : Entity(world , position)
{
	if (TextureManager::instance().get(type))
	{
		m_sprite.setTexture(*TextureManager::instance().get(type));
		m_sprite.setTextureRect(sf::IntRect(0, 0, TextureManager::instance().get(type)->getSize().x,
			TextureManager::instance().get(type)->getSize().y));
	}

	init(b2_staticBody, 0.6f);
	m_radialLight.setRange(50.f);
	m_radialLight.setFade(true);
}

Constants::GiftType Gift::getType() const { return m_type; }

void Gift::update(float dt)
{
	m_pulseTime += dt;  // تراكم داخلي

	m_radialLight.setPosition(getPosition());
	m_radialLight.setColor(sf::Color::Green);

	float pulse = std::sin(m_pulseTime * 2.f);  // تردد 2 Hz (غيّره حسب السرعة)

	float intensity = 0.3f + 0.2f * pulse;
	m_radialLight.setIntensity(intensity);

	float range = 50.f + 20.f * pulse;
	m_radialLight.setRange(range);
}



void Gift::render(RenderLayers& renderLayers) {
	renderLayers.drawLight(m_radialLight);
	renderLayers.drawForeground(m_radialLight);
	renderLayers.drawForeground(m_sprite);
}



void Gift::customizeFixtureDef(b2FixtureDef& fixtureDef)
{
	fixtureDef.isSensor = true; 
}

void Gift::des()
{
	m_visable = false; // Hide the gift after destruction
	setDestroyed(true); // Mark the gift as destroyed

}