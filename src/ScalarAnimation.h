#pragma once

#include "Animation.h"

class ScalarAnimation : public Animation {
public:
    ScalarAnimation(float& t,
                    const float t0,
                    const float t1,
                    const Animator::Motion style,
                    const float delay,
                    const std::shared_ptr<ParticleSystem> particleSystem);
    
    ~ScalarAnimation();
    
    bool Done();
    void Update(const float deltaTime);
    
private:
    float* mT = nullptr;
};
