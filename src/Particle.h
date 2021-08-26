#pragma once

#include "Vector2.h"

struct Particle
{
    float mass;
    Vector2 position;
    Vector2 velocity;

    Particle(const float mass = 1.0f,
             const Vector2& position = Vector2::zero,
             const Vector2& velocity = Vector2::zero);
};
