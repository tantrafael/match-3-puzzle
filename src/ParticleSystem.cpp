#include "ParticleSystem.h"

#include <list>

struct ParticleSystem::ParticleSystemImplementation {
    std::list<std::shared_ptr<Particle>> mParticles;

    ParticleSystemImplementation() {
    }
};

ParticleSystem::ParticleSystem()
: mPimpl(new ParticleSystemImplementation()) {
}

ParticleSystem::~ParticleSystem() {
}

std::shared_ptr<Particle> ParticleSystem::AddParticle(const float mass, const Vector2& position, const Vector2& velocity) {
    std::shared_ptr<Particle> particle;
    particle.reset(new Particle(mass, position, velocity));
    mPimpl->mParticles.push_back(particle);
    
    return particle;
}

void ParticleSystem::RemoveParticle(std::shared_ptr<Particle> particle) {
    if (particle != nullptr) {
        mPimpl->mParticles.remove(particle);
    }
}

void ParticleSystem::Update(const float deltaTime) {
    for (auto& particle : mPimpl->mParticles) {
        particle->position += particle->velocity * deltaTime;
    }
}
