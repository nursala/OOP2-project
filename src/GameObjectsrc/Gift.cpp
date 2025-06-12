#include "GameObject/Gift.h"
#include "GameObject/Player.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"

namespace {
    const bool reg = [] {
        Factory::instance().registerType(TextureID::Gift, [](b2World& world) {
            return std::make_unique<Gift>(world);
            });
        return true;
        }();
}
Gift::Gift(b2World& world)
    : Entity(world, TextureManager::instance().get(TextureID::Gift), { 200,200 }, {1,1}, 0.4f)
{
    // Set up Box2D body as static or kinematic, and set up sprite
    m_sprite.setScale(0.05f, 0.05f);

}

GiftType Gift::getType() const { return m_type; }

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

void Gift::update(float deltaTime) {
    // Optional: animate or rotate the gift

    //m_animation.update(0, 5, deltaTime, true); // Assuming a single frame animation

}

void Gift::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
}
