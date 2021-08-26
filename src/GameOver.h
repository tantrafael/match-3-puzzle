#pragma once

#include <memory>

#include "State.h"

class GameOver : public State {
public:
    GameOver(std::shared_ptr<King::Engine> engine, std::function<void()> exitCallback);
    ~GameOver();

    void Update(const float deltaTime);
    
private:
    bool mMouseDown;
    void HandleMouseInput();
};
