#pragma once

#include "Animation.h"

class VectorAnimation : public Animation {
public:
    VectorAnimation(Vector2& v,
                    const Vector2& v0,
                    const Vector2& v1,
                    const Animator::Motion style,
                    const float delay,
                    const std::shared_ptr<ParticleSystem> particleSystem);
    
    ~VectorAnimation();
    
    bool Done();
    void Update(const float deltaTime);
    
private:
    Vector2* mV = nullptr;
};
