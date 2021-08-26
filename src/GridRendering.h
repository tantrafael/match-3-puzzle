#pragma once

#include "GridOperations.h"
#include <king/Engine.h>

class GridRendering : public GridOperations {
protected:
    Vector2 mPosition;
    float mTileSize;
    std::shared_ptr<King::Engine> mEngine;

    GridRendering(const Vector2Int& dimensions,
                  const int scoringConsecutiveLimit,
                  const std::function<void(std::vector<Item::Type>)> scoreCallback,
                  const Vector2& position,
                  const float tileSize,
                  const std::shared_ptr<King::Engine> engine);

    ~GridRendering();

    bool WithinBounds(const Vector2& pos);
    Vector2Int GridPosition(const Vector2& pos);
    void RenderItems();
    void RenderSelection();
};
