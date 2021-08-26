#include "GridModel.h"

GridModel::GridModel(const Vector2Int& dimensions)
: mDimensions(dimensions)
, mMatrix(Matrix<std::shared_ptr<Item>>(dimensions.y, MatrixRow<std::shared_ptr<Item>>(dimensions.x))) {
}

GridModel::~GridModel() {
    Vector2 dimensions = GetDimensions();
    int rows = dimensions.y;
    int cols = dimensions.x;
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            Vector2Int pos = Vector2Int(col, row);
            DeleteItem(pos);
        }
    }
}

Vector2Int GridModel::GetDimensions() {
    return mDimensions;
}

bool GridModel::ValidPosition(const Vector2Int& pos) {
    Vector2 dimensions = GetDimensions();
    int rows = dimensions.y;
    int cols = dimensions.x;
    
    return ((pos.x >=0) && (pos.x < cols) && (pos.y >= 0) && (pos.y < rows));
}

void GridModel::SetItem(const Vector2Int& pos, std::shared_ptr<Item> item) {
    if (ValidPosition(pos)) {
        mMatrix[pos.y][pos.x] = item;
    }
}

std::shared_ptr<Item> GridModel::GetItem(const Vector2Int& pos) {
    std::shared_ptr<Item> item;
    
    if (ValidPosition(pos)) {
        item = mMatrix[pos.y][pos.x];
    }
    
    return item;
}

void GridModel::DeleteItem(const Vector2Int& pos) {
    std::shared_ptr<Item> item = GetItem(pos);
    item.reset();
    SetItem(pos, nullptr);
}

void GridModel::SelectPosition(const Vector2Int& pos) {
    mSelectedPos.reset(new Vector2Int(pos));
}

std::shared_ptr<Vector2Int> GridModel::GetSelectedPosition() {
    return mSelectedPos;
}

void GridModel::ClearSelectedPosition() {
    mSelectedPos.reset();
}
