#pragma once

#include "GridModel.h"
#include "Vector2Int.h"

class GridValidation : public GridModel {
protected:
    int mScoringConsecutiveLimit;

    GridValidation(const Vector2Int& dimensions, const int scoringConsecutiveLimit);
    ~GridValidation();

    bool ValidSwap(const Vector2Int& pos_0, const Vector2Int& pos_1);
    bool ValidMove(Vector2Int pos_0, Vector2Int pos_1);
};
