#pragma once

#include <memory>

#include "State.h"
#include "Grid.h"

class Play : public State {
public:
    static const int TimeLimit = 60;

    Play(std::shared_ptr<King::Engine> engine,
         std::function<void()> exitCallback,
         std::function<void(int)> timeCallback,
         std::function<void(int)> scoreCallback);

    ~Play();

    void Update(const float deltaTime);

private:
    std::function<void(int)> mTimeCallback;
    std::function<void(int)> mScoreCallback;
    Grid mGrid;
    bool mMouseDown;
    float mTime;
    int mSeconds;
    int mScore;

    void HandleMouseInput();
    void UpdateScore(std::vector<Item::Type> itemTypes);
};
