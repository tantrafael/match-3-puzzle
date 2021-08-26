#include "Animator.h"

#include <map>
#include <vector>
#include <list>

#include "VectorAnimation.h"
#include "ScalarAnimation.h"
#include "ParticleSystem.h"

struct Animator::AnimatorImplementation {
    std::list<std::shared_ptr<Animation>> mAnimations;
    std::shared_ptr<ParticleSystem> mParticleSystem;
    bool mIdle;

    AnimatorImplementation()
    : mParticleSystem(new ParticleSystem())
    , mIdle(true) {
    }
};

Animator::Animator()
: mPimpl(new AnimatorImplementation()) {
}

Animator::~Animator() {
}

bool Animator::Idle() {
    return mPimpl->mIdle;
}

void Animator::Animate(Vector2& v, const Vector2& v0, const Vector2& v1, const Motion style, const float delay) {
    std::shared_ptr<class Animation> animation;
    animation.reset(new VectorAnimation(v, v0, v1, style, delay, mPimpl->mParticleSystem));
    mPimpl->mAnimations.push_back(animation);
    mPimpl->mIdle = false;
}

void Animator::Animate(float& t, const float t0, const float t1, const Motion style, const float delay) {
    std::shared_ptr<Animation> animation;
    animation.reset(new ScalarAnimation(t, t0, t1, style, delay, mPimpl->mParticleSystem));
    mPimpl->mAnimations.push_back(animation);
    mPimpl->mIdle = false;
}

void Animator::Update(const float deltaTime) {
    std::list<std::shared_ptr<Animation>>::iterator it = mPimpl->mAnimations.begin();

    while (it != mPimpl->mAnimations.end()) {
        std::shared_ptr<Animation> animation = *it;
        animation->Update(deltaTime);
        
        if (animation->Done()) {
            it = mPimpl->mAnimations.erase(it);
        } else {
            it++;
        }
    }

    if (!mPimpl->mIdle && (mPimpl->mAnimations.size() == 0)) {
        mPimpl->mIdle = true;
    }
    
    mPimpl->mParticleSystem->Update(deltaTime);
}
