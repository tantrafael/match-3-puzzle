#pragma once

#include <memory>

#include "Particle.h"

class ParticleSystem {
public:
    ParticleSystem();
    ~ParticleSystem();

    std::shared_ptr<Particle> AddParticle(const float mass = 1.0f,
                                          const Vector2& position = Vector2::zero,
                                          const Vector2& velocity = Vector2::zero);

    void RemoveParticle(const std::shared_ptr<Particle> particle);
    void Update(const float deltaTime);
    
private:
    struct ParticleSystemImplementation;
    std::unique_ptr<ParticleSystemImplementation> mPimpl;
};
