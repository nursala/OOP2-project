#include "GameObject/Gift.h"
#include "GameObject/Player.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"


Gift::Gift(World& world)
    : Entity(world, TextureManager::instance().get(TextureID::Gift), { 200,200 }, { 1,1 }, 0.4f)
{
    // Set up Box2D body as static or kinematic, and set up sprite
    m_visable = true;

}

GiftType Gift::getType() const { return m_type; }

void Gift::update(float deltaTime)
{
	if (m_body) {
		b2Vec2 pos = m_body->GetPosition();
		m_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);
	}
}

void Gift::render(sf::RenderWindow& window)
{
	if (isVisible())
	window.draw(m_sprite);
}

//void Gift::apply(Player& player) {
//    //switch (m_type) {
//    //case GiftType::Armor:
//    //    player.addArmor(25); // You need to implement addArmor in Player
//    //    break;
//    //case GiftType::Life:
//    //    player.addLife(20); // You need to implement addLife in Player
//    //    break;
//    //case GiftType::Ammo:
//    //    player.addAmmo(10); // You need to implement addAmmo in Player or Weapon
//    //    break;
//    //}
//}
//
