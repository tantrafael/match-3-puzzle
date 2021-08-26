#pragma once

#include <memory>

#include "Vector2.h"

class Animator {
public:
    enum Motion {
        MOTION_SMOOTH,
        MOTION_BOUNCY
    };

    Animator();
    ~Animator();
    
    void Animate(Vector2& v,
                 const Vector2& v0,
                 const Vector2& v1,
                 const Motion style = MOTION_SMOOTH,
                 const float delay = 0.0f);

    void Animate(float& t,
                 const float t0,
                 const float t1,
                 const Motion style = MOTION_SMOOTH,
                 const float delay = 0.0f);

    void Update(const float deltaTime);
    bool Idle();

private:
    struct AnimatorImplementation;
    std::unique_ptr<AnimatorImplementation> mPimpl;
};

