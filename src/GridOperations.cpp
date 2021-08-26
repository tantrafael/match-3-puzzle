#include "GridOperations.h"

#include <functional>

GridOperations::GridOperations(const Vector2Int& dimensions,
                               const int scoringConsecutiveLimit,
                               const std::function<void(std::vector<Item::Type>)> scoreCallback)
: GridActions(dimensions, scoringConsecutiveLimit)
, mScoreCallback(scoreCallback) {
}

GridOperations::~GridOperations() {
}

void GridOperations::Fill() {
    srand((int) time(0));
    
    Vector2 dimensions = GetDimensions();
    int rows = dimensions.y;
    int cols = dimensions.x;
    
    int counter_row = 0;
    Item::Type accumulationType_row = Item::TYPE_MAX;
    std::vector<int> counter_cols(cols);
    std::vector<Item::Type> accumulationType_cols(cols);
    
    for (int col = 0; col < cols; col++) {
        counter_cols[col] = 0;
        accumulationType_cols[col] = Item::TYPE_MAX;
    }
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // Initialize consecutive type counters.
            if (col == 0) {
                counter_row = 0;
                accumulationType_row = Item::TYPE_MAX;
            }
            
            int counter_col = counter_cols[col];
            Item::Type accumulationType_col = accumulationType_cols[col];
            
            // Find a type that doesn't result in a scoring combination.
            int index = rand() % Item::TYPE_MAX;
            Item::Type type = static_cast<Item::Type>(index);
            bool counterAtLimit_row = (counter_row == mScoringConsecutiveLimit - 1);
            bool counterAtLimit_col = (counter_col == mScoringConsecutiveLimit - 1);
            
            if (counterAtLimit_row || counterAtLimit_col) {
                bool overflow_row = counterAtLimit_row && (type == accumulationType_row);
                bool overflow_col = counterAtLimit_col && (type == accumulationType_col);
                
                while (overflow_row || overflow_col) {
                    index = rand() % Item::TYPE_MAX;
                    type = static_cast<Item::Type>(index);
                    overflow_row = counterAtLimit_row && (type == accumulationType_row);
                    overflow_col = counterAtLimit_col && (type == accumulationType_col);
                }
            }
            
            // Update consecutive type counters.
            if (type == accumulationType_row) {
                counter_row++;
            } else {
                accumulationType_row = type;
                counter_row = 1;
            }
            
            if (type == accumulationType_col) {
                counter_cols[col]++;
            } else {
                accumulationType_cols[col] = type;
                counter_cols[col] = 1;
            }
            
            // Create and add new item.
            std::shared_ptr<Item> item;
            item.reset(new Item());
            item->type = type;
            
            Vector2Int gridPos = Vector2Int(col, row);
            Vector2Int startPos = gridPos;
            startPos.y -= rows;
            float delay = GetDelay(gridPos, rows, cols);

            SetItem(gridPos, item);
            Move(item, static_cast<Vector2>(startPos), static_cast<Vector2>(gridPos), delay);
        }
    }
}

void GridOperations::Hit(const Vector2Int& pos) {
    if (mSelectedPos == nullptr) {
        SelectPosition(pos);
    } else {
        if (ValidSwap(*mSelectedPos, pos)) {
            SwapItems(*mSelectedPos, pos);
        }
        
        ClearSelectedPosition();
    }
}

void GridOperations::SwapItems(const Vector2Int& pos_0, const Vector2Int& pos_1) {
    std::shared_ptr<Item> item_0 = GetItem(pos_0);
    std::shared_ptr<Item> item_1 = GetItem(pos_1);
    SetItem(pos_1, item_0);
    SetItem(pos_0, item_1);
    Move(item_0, static_cast<Vector2>(pos_0), static_cast<Vector2>(pos_1));
    Move(item_1, static_cast<Vector2>(pos_1), static_cast<Vector2>(pos_0));
    AddPendingAction(std::bind(&GridOperations::FindCombinations, this));
}

void GridOperations::FindCombinations() {
    Vector2 dimensions = GetDimensions();
    int rows = dimensions.y;
    int cols = dimensions.x;
    
    std::vector<Vector2Int> combinations;
    
    // Create consecutive type counters, horizontal and vertical.
    std::vector<Vector2Int> accumulator_row;
    Item::Type accumulationType_row = Item::TYPE_MAX;
    std::vector<std::vector<Vector2Int>> accumulator_cols(cols);
    std::vector<Item::Type> accumulationType_cols(cols);
    
    for (int col = 0; col < cols; col++) {
        accumulationType_cols[col] = Item::TYPE_MAX;
    }
    
    // Traverse grid once.
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            Vector2Int pos = Vector2Int(col, row);
            std::shared_ptr<Item> item = GetItem(pos);
            
            if (item != nullptr) {
                Item::Type type = item->type;
                
                // Check if the position is part of a combination, horizontally and vertically.
                CheckForCombinations(pos, type, accumulator_row, accumulationType_row, combinations, col, cols);
                CheckForCombinations(pos, type, accumulator_cols[col], accumulationType_cols[col], combinations, row, rows);
            }
        }
    }
    
    // Remove duplicates of found positions.
    std::vector<Vector2Int>::iterator it;
    it = std::unique(combinations.begin(), combinations.end());
    long uniqueSize = std::distance(combinations.begin(), it);
    combinations.resize(uniqueSize, Vector2Int::zero);
    
    // Animate and remove affected items.
    if (combinations.size() > 0) {
        for (auto& pos : combinations) {
            std::shared_ptr<Item> item = GetItem(pos);
            Scale(item, item->scale, 0.0f);
        }
        
        AddPendingAction(std::bind(&GridOperations::ReleaseCombinations, this));
    }
    
    // Update score
    if (combinations.size() > 0) {
        std::vector<Item::Type> itemTypes;
        
        for (auto& pos : combinations) {
            std::shared_ptr<Item> item = GetItem(pos);
            itemTypes.push_back(item->type);
        }
        
        mScoreCallback(itemTypes);
    }

    mCombinations = combinations;
}

void GridOperations::CheckForCombinations(const Vector2Int& pos,
                                          const Item::Type& type,
                                          std::vector<Vector2Int>& accumulator,
                                          Item::Type& accumulationType,
                                          std::vector<Vector2Int>& combinations,
                                          const int index,
                                          const int limit) {
    if (type != accumulationType) {
        if (accumulator.size() >= mScoringConsecutiveLimit) {
            combinations.insert(combinations.end(), accumulator.begin(), accumulator.end());
        }
        
        accumulator.clear();
        accumulationType = type;
    }
    
    accumulator.push_back(pos);
    
    if (index == limit - 1) {
        if (accumulator.size() >= mScoringConsecutiveLimit) {
            combinations.insert(combinations.end(), accumulator.begin(), accumulator.end());
        }
        
        accumulator.clear();
        accumulationType = Item::TYPE_MAX;
    }
}

void GridOperations::ReleaseCombinations() {
    for (auto& pos : mCombinations) {
        DeleteItem(pos);
    }
    
    CollapseRefill();
}

void GridOperations::CollapseRefill() {
    Vector2 dimensions = GetDimensions();
    int rows = dimensions.y;
    int cols = dimensions.x;
    
    for (int col = 0; col < cols; col++) {
        int lowestEmptyRow = rows;
        std::vector<std::shared_ptr<Item>> refills;
        
        for (int row = rows - 1; row >= 0; row--) {
            Vector2Int pos = Vector2Int(col, row);
            std::shared_ptr<Item> item = GetItem(pos);
            
            if (item == nullptr) {
                if (lowestEmptyRow == rows) {
                    lowestEmptyRow = row;
                }
                
                int index = rand() % Item::TYPE_MAX;
                Item::Type type = static_cast<Item::Type>(index);
                std::shared_ptr<Item> refill(new Item());
                refill->type = type;
                refills.push_back(refill);
            } else {
                if (lowestEmptyRow < rows) {
                    Vector2Int lowestEmptyPos = Vector2Int(col, lowestEmptyRow);
                    float delay = GetDelay(lowestEmptyPos, rows, cols);
                    SetItem(pos, nullptr);
                    SetItem(lowestEmptyPos, item);
                    Move(item, item->pos, static_cast<Vector2>(lowestEmptyPos), delay);
                    lowestEmptyRow--;
                }
            }
        }
        
        int nrRefills = static_cast<int>(refills.size());
        int i = 1;
        
        for (auto& item : refills) {
            int row = nrRefills - i;
            Vector2Int gridPos = Vector2Int(col, row);
            Vector2 targetPos = static_cast<Vector2>(gridPos);
            Vector2 startPos = targetPos;
            startPos.y = static_cast<float>(-i);
            float delay = GetDelay(gridPos, rows, cols);
            SetItem(gridPos, item);
            Move(item, startPos, targetPos, delay);

            i++;
        }
    }
    
    if (!mAnimator.Idle()) {
        AddPendingAction(std::bind(&GridOperations::FindCombinations, this));
    }
}

float GridOperations::GetDelay(const Vector2Int& pos, const int rows, const int cols) {
    float delay = 0.01f * (static_cast<float>(rows - pos.y - 1) + 2.0f * static_cast<float>(pos.x));
    return delay;
}
