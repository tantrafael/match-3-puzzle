#include "GridActions.h"

GridActions::GridActions(const Vector2Int& dimensions, const int scoringConsecutiveLimit)
: GridValidation(dimensions, scoringConsecutiveLimit)
, mAvailable(false) {
}

GridActions::~GridActions() {
}

void GridActions::Move(const std::shared_ptr<Item> item, const Vector2& pos_0, const Vector2& pos_1, const float delay) {
    if (item != nullptr) {
        mAvailable = false;
        mAnimator.Animate(item->pos, pos_0, pos_1, Animator::MOTION_BOUNCY, delay);
    }
}

void GridActions::Scale(const std::shared_ptr<Item> item, const float scale_0, const float scale_1) {
    if (item != nullptr) {
        mAvailable = false;
        mAnimator.Animate(item->scale, scale_0, scale_1, Animator::MOTION_SMOOTH, 0.0f);
    }
}

void GridActions::AddPendingAction(std::function<void()> callback) {
    mActions.push_back(callback);
}

void GridActions::PerformPendingAction() {
    if (mActions.size() > 0) {
        std::vector<std::function<void()>>::iterator it = mActions.begin();
        std::function<void()> callback = *it;
        mActions.erase(it);
        callback();
    }
}
