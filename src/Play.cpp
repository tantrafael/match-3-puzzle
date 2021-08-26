#include "Play.h"

#include <math.h>

Play::Play(std::shared_ptr<King::Engine> engine,
           std::function<void()> exitCallback,
           std::function<void(int)> timeCallback,
           std::function<void(int)> scoreCallback)
: State(engine, exitCallback)
, mTimeCallback(timeCallback)
, mScoreCallback(scoreCallback)
, mGrid(Vector2Int(8, 8),
        3,
        std::bind(&Play::UpdateScore, this, std::placeholders::_1),
        Vector2(326.0f, 96.0f),
        43.0f,
        engine)
, mMouseDown(mEngine->GetMouseButtonDown())
, mTime(static_cast<float>(TimeLimit))
, mSeconds(TimeLimit)
, mScore(0) {
    mScoreCallback(0);
    mTimeCallback(mSeconds);
}

Play::~Play() {
}

void Play::Update(const float deltaTime) {
    HandleMouseInput();
    mGrid.Update(deltaTime);
    mGrid.Render();

    mTime -= deltaTime;

    if (static_cast<int>(ceil(mTime)) == mSeconds - 1) {
        mSeconds--;
        mTimeCallback(mSeconds);
    }
    
    if (mSeconds == 0) {
        mExitCallback();
    }
}

void Play::HandleMouseInput() {
    if (mEngine->GetMouseButtonDown()) {
        if (!mMouseDown) {
            mMouseDown = true;
        }

        Vector2 pos = Vector2(mEngine->GetMouseX(), mEngine->GetMouseY());
        mGrid.Interact(pos);
    } else {
        if (mMouseDown) {
            mMouseDown = false;
        }
    }
}

void Play::UpdateScore(std::vector<Item::Type> itemTypes) {
    mScore += 100 * static_cast<int>(itemTypes.size()) - 200;
    mScoreCallback(mScore);
}
