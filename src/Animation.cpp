#include "Animation.h"

#include <map>
#include <vector>

#include "Particle.h"

static std::map<Animator::Motion, MotionParameters> MotionParametersMap {
    { Animator::MOTION_SMOOTH, MotionParameters {200.0f, 25.0f, 0.0001f} },
    { Animator::MOTION_BOUNCY, MotionParameters {300.0f, 15.0f, 0.00001f} }
};

Animation::Animation(const Animator::Motion style,
                     const float delay,
                     const std::shared_ptr<ParticleSystem> particleSystem)

: mDelay(delay)
, mTime(0.0f)
, mStarted(delay == 0.0f)
, mDone(false)
, mParticleSystem(particleSystem) {
    mParticle = particleSystem->AddParticle();
    mMotionParameters = MotionParametersMap[style];
}

Animation::~Animation() {
    if (mParticleSystem != nullptr) {
        mParticleSystem->RemoveParticle(mParticle);
    }
}

bool Animation::Done() {
    return mDone;
}

void Animation::Update(const float deltaTime) {
    if (!mStarted) {
        mTime += deltaTime;

        if (mTime >= mDelay) {
            mStarted = true;
        }
    } else {
        Vector2 springForce = (mV1 - mParticle->position) * mMotionParameters.SpringConstant;
        Vector2 dampingForce = -mParticle->velocity * mMotionParameters.DampingCoefficient;
        Vector2 force = springForce + dampingForce;
        Vector2 acceleration = force / mParticle->mass;
        mParticle->velocity += acceleration * deltaTime;
        
        if (!mDone && (mParticle->velocity.sqrMagnitude() < mMotionParameters.MotionLimit)) {
            mParticle->position = mV1;
            mParticle->velocity = Vector2::zero;
            mDone = true;
        }
    }
}
