#pragma once  
#include "GameObject/Entity.h" 


enum class GiftType { ARMOR, HEALTH,ENEMYSPEEDDOWN,SPEEDUP,SPY};

class Gift : public Entity {  
public:  
	Gift(World& world, const sf::Texture* texture, sf::Vector2f position, sf::Vector2u imageCount);
	GiftType getType() const;  
    //virtual void apply(Player& player) = 0; // Applies the effect to the player  
    void update(float deltaTime) override;  
    void render(sf::RenderWindow& window) override;  
   void des();  

protected:  
   GiftType m_type;  
   World& m_world;  
};
