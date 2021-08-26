#pragma once

#include <vector>
#include <functional>

#include "GridValidation.h"
#include "Animator.h"

class GridActions : public GridValidation {
protected:
    std::vector<std::function<void()>> mActions;
    Animator mAnimator;
    bool mAvailable;

    GridActions(const Vector2Int& dimensions, const int scoringConsecutiveLimit);
    ~GridActions();

    void Move(const std::shared_ptr<Item> item, const Vector2& pos_0, const Vector2& pos_1, const float delay = 0.0f);
    void Scale(const std::shared_ptr<Item> item, const float scale_0, const float scale_1);
    void AddPendingAction(std::function<void()> callback);
    void PerformPendingAction();
};
