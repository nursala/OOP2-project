#include "Game.h"
#include <iostream>
#include <cmath>
#include <algorithm>

constexpr float SCALE = 30.f; // 1 متر = 30 بكسل

Game::Game()
	: window(sf::VideoMode(1280, 720), "Bullet Echo Light Demo")
	, world(b2Vec2(0.f, 0.f))
	, debugDraw(&window)
	, m_tileMap("map.json")
	, light(100.f, 720),
	enemy(world, { 200.f, 150.f })

{

	window.setFramerateLimit(60);

	// تحميل صورة الخريطة فقط للرسم (لو في صورة)
	if (!mapTexture.loadFromFile("map.png")) {
		std::cerr << "Failed to load map.png!\n";
		std::exit(-1);
	}
	mapSprite.setTexture(mapTexture);

	// إعداد اللاعب في SFML
	float playerRadius = 5;
	player.setRadius(playerRadius);
	player.setFillColor(sf::Color::Cyan);
	player.setOrigin(playerRadius, playerRadius);

	// إضافة اللاعب إلى Box2D (دائرة)
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(100 / SCALE, 100 / SCALE);
	playerBody = world.CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = playerRadius / SCALE;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.0f;
	playerBody->CreateFixture(&fixtureDef);

	player.setPosition(100, 100);

	view.setSize(window.getSize().x / 3.f, window.getSize().y / 3.f);

	debugDraw.SetFlags(b2Draw::e_shapeBit);
	world.SetDebugDraw(&debugDraw);

	// إنشاء أجسام الجدران من الخريطة (يفترض أنك تحسب SCALE داخل الكلاس)
	m_tileMap.createCollisionObjects(world, "walls");
}

void Game::run() {
	while (window.isOpen()) {
		float dt = clock.restart().asSeconds();
		processEvents();
		update(dt);
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::update(float dt) {
	// حساب اتجاه الحركة (بوحدة متر/ثانية)
	b2Vec2 velocity(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y -= PLAYER_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y += PLAYER_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x -= PLAYER_SPEED;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x += PLAYER_SPEED;
	playerBody->SetLinearVelocity(velocity);

	// حدث موقع دائرة SFML ليطابق موقع الجسم الفيزيائي
	b2Vec2 pos = playerBody->GetPosition();
	player.setPosition(pos.x * SCALE, pos.y * SCALE);

	// تحديث الكاميرا حول اللاعب
	sf::Vector2f center = player.getPosition();
	sf::Vector2f viewSize = view.getSize();
	center.x = std::clamp(center.x, viewSize.x / 2.f, (float)mapTexture.getSize().x - viewSize.x / 2.f);
	center.y = std::clamp(center.y, viewSize.y / 2.f, (float)mapTexture.getSize().y - viewSize.y / 2.f);
	view.setCenter(center);
	window.setView(view);

	// تحديث فيزياء Box2D
	world.Step(dt, 8, 3);

	// حساب زاوية اتجاه الماوس
	sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	float angleToMouse = std::atan2(mouseWorld.y - player.getPosition().y, mouseWorld.x - player.getPosition().x);
	float fov = 3.14f / 3.f; // 60 درجة

	// تحديث الإضاءة
	light.update(player.getPosition(), angleToMouse, fov, world);
	enemy.update(dt);
}

void Game::render() {
	window.clear();

	window.draw(mapSprite);       // رسم الخريطة
	light.draw(window);           // رسم الضوء
	window.draw(player);          // رسم اللاعب
	enemy.draw(window);
	world.DebugDraw();            // رسم debug
	window.display();
}
