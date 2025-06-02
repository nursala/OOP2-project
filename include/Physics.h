#pragma once

#include <box2d/b2_world.h>

class Physics {
public:
    static void init();
    static void update(float deltaTime);

    static b2World world;
    static constexpr float SCALE = 100.0f;  // Example scale
private:
    static float elapsedTime;
};
