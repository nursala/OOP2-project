#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(b2World& world, const sf::Vector2f& pos, float radius = 16.f, float scale = 30.f)
        : m_radius(radius), m_visible(true), m_lastSeen(0.f), SCALE(scale)
    {
        // Box2D body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pos.x / SCALE, pos.y / SCALE);
        m_body = world.CreateBody(&bodyDef);

        b2CircleShape shape;
        shape.m_radius = radius / SCALE;

        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        fixDef.density = 1.f;
        fixDef.friction = 0.2f;
        // اربط العدو مع الفيكسشر (double dispatch)
        fixDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
        m_body->CreateFixture(&fixDef);

        // SFML shape
        m_shape.setRadius(radius);
        m_shape.setOrigin(radius, radius);
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setPosition(pos);
    }

    // دالة يستدعيها الضوء عند كشف العدو (double dispatch)
    void onLightCollision() {
        m_visible = true;
        m_lastSeen = 0.f; // صفّر العداد
    }

    // تحديث العدو: يخفي نفسه إذا لم يكشفه الضوء مؤخرًا
    void update(float dt) {
        m_lastSeen += dt;
        if (m_lastSeen > 0.2f) m_visible = false; // يخفي نفسه بعد 0.2 ثانية من فقدان الضوء
        // حدث مكان الشكل
        b2Vec2 pos = m_body->GetPosition();
        m_shape.setPosition(pos.x * SCALE, pos.y * SCALE);
    }

    // رسم العدو فقط إذا كان ظاهر
    void draw(sf::RenderTarget& target) {
        if (m_visible)
            target.draw(m_shape);
    }

    // Getter
    b2Body* getBody() { return m_body; }
    bool isVisible() const { return m_visible; }

private:
    b2Body* m_body = nullptr;
    sf::CircleShape m_shape;
    float m_radius;
    bool m_visible;
    float m_lastSeen; // كم مر وقت من آخر كشف للضوء
    const float SCALE;
};
