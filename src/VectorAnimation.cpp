#include "VectorAnimation.h"

VectorAnimation::VectorAnimation(Vector2& v,
                                 const Vector2& v0,
                                 const Vector2& v1,
                                 const Animator::Motion style,
                                 const float delay,
                                 const std::shared_ptr<ParticleSystem> particleSystem)
: Animation(style, delay, particleSystem)
, mV(&v) {
    mV0 = v0;
    mV1 = v1;
    mParticle->position = mV0;
    *mV = mV0;
}

VectorAnimation::~VectorAnimation() {
}

void VectorAnimation::Update(const float deltaTime) {
    Animation::Update(deltaTime);
    *mV = mParticle->position;
}
