#pragma once

#include <vector>

#include "GridActions.h"
#include "Vector2Int.h"

class GridOperations : public GridActions {
protected:
    std::function<void(std::vector<Item::Type>)> mScoreCallback;
    std::vector<Vector2Int> mCombinations;

    GridOperations(const Vector2Int& dimensions,
                   const int scoringConsecutiveLimit,
                   const std::function<void(std::vector<Item::Type>)> scoreCallback);

    ~GridOperations();
    
    void Fill();
    void Hit(const Vector2Int& pos);
    void SwapItems(const Vector2Int& pos_0, const Vector2Int& pos_1);
    void FindCombinations();
    void CheckForCombinations(const Vector2Int& pos,
                              const Item::Type& type,
                              std::vector<Vector2Int>& accumulator,
                              Item::Type& accumulationType,
                              std::vector<Vector2Int>& combinations,
                              const int index,
                              const int limit);
    void ReleaseCombinations();
    void CollapseRefill();
    float GetDelay(const Vector2Int& pos, const int rows, const int cols);
};
