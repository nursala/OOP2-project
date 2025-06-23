#pragma once  
#include "GameObject/Entity.h" 


enum class GiftType { ARMOR, HEALTH, ENEMYSPEEDDOWN, SPEEDUP, SPY, SIZE};

class Gift : public Entity {  
public:  
	Gift(World& world, const sf::Texture* texture);
	GiftType getType() const;  
	void setType(GiftType type) { m_type = type; }
    //virtual void apply(Player& player) = 0; // Applies the effect to the player  
    void update(float deltaTime) override;  
    void render(sf::RenderWindow& window) override;  
     b2BodyType getBodyType() const override { return b2_staticBody; } ;
     void customizeFixtureDef(b2FixtureDef& fixtureDef);
   void des();  

protected:  
   GiftType m_type;  
   World& m_world;  
};
