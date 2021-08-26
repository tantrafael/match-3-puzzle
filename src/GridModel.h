#pragma once

#include <memory>
#include <vector>

#include "Vector2Int.h"
#include "Item.h"

template <class T>
using MatrixRow = std::vector<T>;

template <class T>
using Matrix = std::vector<MatrixRow<T>>;

class GridModel {
protected:
    Vector2Int mDimensions;
    Matrix<std::shared_ptr<Item>> mMatrix;
    std::shared_ptr<Vector2Int> mSelectedPos;

    GridModel(const Vector2Int& dimensions);
    ~GridModel();

    Vector2Int GetDimensions();
    bool ValidPosition(const Vector2Int& pos);
    void SetItem(const Vector2Int& pos, std::shared_ptr<Item> item);
    std::shared_ptr<Item> GetItem(const Vector2Int& pos);
    void DeleteItem(const Vector2Int& pos);

    void SelectPosition(const Vector2Int& pos);
    std::shared_ptr<Vector2Int> GetSelectedPosition();
    void ClearSelectedPosition();
};
