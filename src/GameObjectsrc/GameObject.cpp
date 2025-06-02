#include "GameObject/GameObject.h"

GameObject::GameObject(b2World* world, const b2Vec2& position) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position = position;
    m_body = world->CreateBody(&bodyDef);
}

GameObject::~GameObject() {
    if (m_body && m_body->GetWorld()) {
        m_body->GetWorld()->DestroyBody(m_body);
    }
}

b2Body* GameObject::getBody() const { return m_body; }

b2Vec2 GameObject::getPosition() const {
    return m_body ? m_body->GetPosition() : b2Vec2(0.0f, 0.0f);
}

void GameObject::setPosition(const b2Vec2& position) {
    if (m_body) m_body->SetTransform(position, m_body->GetAngle());
}

void GameObject::setTexture(std::shared_ptr<sf::Texture> texture)
{
	if (texture) {
		m_sprite.setTexture(*texture);
		m_sprite.setOrigin(texture->getSize().x / 2.0f, texture->getSize().y / 2.0f);
	}
}

void GameObject::render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
}

void GameObject::createFixture(const b2Shape& shape, float density) {
    if (m_body) {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;
        m_body->CreateFixture(&fixtureDef);
    }
}

void GameObject::setUserData(void* data) {
    if (m_body) m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(data);
}

void* GameObject::getUserData() const {
    return m_body ? reinterpret_cast<void*>(m_body->GetUserData().pointer) : nullptr;
}