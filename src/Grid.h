#pragma once

#include <memory>

#include "Vector2Int.h"
#include "Item.h"
#include "GridRendering.h"
#include <king/Engine.h>

class Grid : public GridRendering {
public:
    Grid(const Vector2Int& dimensions,
         const int scoringConsecutiveLimit,
         const std::function<void(std::vector<Item::Type>)> scoreCallback,
         const Vector2& position,
         const float tileSize,
         const std::shared_ptr<King::Engine> engine);

    ~Grid();

    void Interact(const Vector2& pos);
    void Update(const float deltaTime);
    void Render();
};
