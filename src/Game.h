#pragma once

#include <memory>

#include <king/Engine.h>
#include <king/Updater.h>

#include "State.h"

class Game : public King::Updater {
public:
    enum GameState {
        STATE_INTRO,
        STATE_PLAY,
        STATE_GAME_OVER
    };

    Game();
    ~Game();

    void Start();

private:
    std::shared_ptr<King::Engine> mEngine;
    GameState mGameState;
    std::unique_ptr<State> mState;
    int mTime;
    int mScore;

    void RenderBackground();
    void RenderTime();
    void RenderScore();
    void EnterState(const GameState state);
    void ExitState();
    void SetTime(const int seconds);
    void SetScore(const int score);
    void Update();
};
