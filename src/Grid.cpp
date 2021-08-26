#include "Grid.h"

Grid::Grid(const Vector2Int& dimensions,
           const int scoringConsecutiveLimit,
           const std::function<void(std::vector<Item::Type>)> scoreCallback,
           const Vector2& position,
           const float tileSize,
           const std::shared_ptr<King::Engine> engine)
: GridRendering(dimensions, scoringConsecutiveLimit, scoreCallback, position, tileSize, engine) {
    Fill();
}
    
Grid::~Grid() {
}

void Grid::Interact(const Vector2& pos) {
    if (mAvailable && WithinBounds(pos)) {
        std::shared_ptr<Vector2Int> selectedPos = GetSelectedPosition();
        Vector2Int gridPos = GridPosition(pos);

        if ((selectedPos == nullptr) || (gridPos != *selectedPos)) {
            Hit(gridPos);
        }
    }
}

void Grid::Update(const float deltaTime) {
    mAnimator.Update(deltaTime);
    
    if (!mAvailable && mAnimator.Idle()) {
        mAvailable = true;
        PerformPendingAction();
    }
}

void Grid::Render() {
    RenderItems();
    RenderSelection();
}
