#pragma once

#include <memory>
#include <functional>

#include <king/Engine.h>

class State {
public:
    State(std::shared_ptr<King::Engine> engine, std::function<void()> exitCallback);
    ~State();

    virtual void Update(const float deltaTime) = 0;
    
protected:
    std::shared_ptr<King::Engine> mEngine;
    std::function<void()> mExitCallback;
};
