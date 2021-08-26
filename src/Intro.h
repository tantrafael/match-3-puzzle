#pragma once

#include <memory>

#include "State.h"

class Intro : public State {
public:
    Intro(std::shared_ptr<King::Engine> engine, std::function<void()> exitCallback);
    ~Intro();

    void Update(const float deltaTime);

private:
    void HandleMouseInput();
};
