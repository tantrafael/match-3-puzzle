#pragma once

#include <memory>

#include "Vector2.h"
#include "Animator.h"
#include "ParticleSystem.h"

struct MotionParameters {
    float SpringConstant;
    float DampingCoefficient;
    float MotionLimit;
};

class Animation {
public:
    Animation(const Animator::Motion style,
              const float delay,
              const std::shared_ptr<ParticleSystem> particleSystem);

    ~Animation();
    
    bool Done();
    virtual void Update(const float deltaTime);

protected:
    Vector2 mV0;
    Vector2 mV1;
    std::shared_ptr<Particle> mParticle;

private:
    float mDelay;
    float mTime;
    bool mStarted;
    bool mDone;
    std::shared_ptr<ParticleSystem> mParticleSystem;
    MotionParameters mMotionParameters;
};
