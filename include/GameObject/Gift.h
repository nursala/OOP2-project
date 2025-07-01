#pragma once  
#include "GameObject/Entity.h" 
#include "candle/RadialLight.hpp"

class Gift : public Entity {  
public:  
	Gift(World& world, sf::Texture* texture, Constants::GiftType& type, sf::Vector2f& pos);
	Constants::GiftType getType() const;

	void update(float deltaTime) override;
	void render(RenderLayers& renderLayers);
	b2BodyType getBodyType() const override { return b2_staticBody; };
	void customizeFixtureDef(b2FixtureDef& fixtureDef);
	void des();

protected:
	Constants::GiftType m_type;
	World& m_world;
	candle::RadialLight m_radialLight;
	float m_pulseTime = 0.f;

};
