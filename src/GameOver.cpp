#include "GameOver.h"

GameOver::GameOver(std::shared_ptr<King::Engine> engine, std::function<void()> exitCallback)
: State(engine, exitCallback)
, mMouseDown(mEngine->GetMouseButtonDown()) {
}

GameOver::~GameOver() {
}

void GameOver::Update(const float deltaTime) {
    HandleMouseInput();
    mEngine->Write("Game over", 410.0f, 230.0f);
    mEngine->Write("Play again", 410.0f, 270.0f);
}

void GameOver::HandleMouseInput() {
    if (mEngine->GetMouseButtonDown()) {
        if (!mMouseDown) {
            mMouseDown = true;
            mExitCallback();
        }
    } else {
        if (mMouseDown) {
            mMouseDown = false;
        }
    }
}
