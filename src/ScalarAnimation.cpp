#include "ScalarAnimation.h"

ScalarAnimation::ScalarAnimation(float& t,
                                 const float t0,
                                 const float t1,
                                 const Animator::Motion style,
                                 const float delay,
                                 const std::shared_ptr<ParticleSystem> particleSystem)
: Animation(style, delay, particleSystem)
, mT(&t) {
    mV0 = Vector2(t0, 0.0f);
    mV1 = Vector2(t1, 0.0f);
    mParticle->position = mV0;
    *mT = t0;
}

ScalarAnimation::~ScalarAnimation() {
}

void ScalarAnimation::Update(const float deltaTime) {
    Animation::Update(deltaTime);
    *mT = mParticle->position.x;
}
