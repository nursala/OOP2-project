#include "GameObject/Gift.h"
#include "GameObject/Player.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "WorldInc/World.h"
#include <iostream> 

Gift::Gift(World& world, const sf::Texture* texture) : Entity(world, texture,  {100, 100}, {1, 1}, 0.4f),
m_world(world)
{

	init(b2_staticBody, 0.6f);
	m_radialLight.setRange(50.f);
	m_radialLight.setFade(true);
	//if(m_type == GiftType::SPY)
}

GiftType Gift::getType() const { return m_type; }

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


