#include "GridValidation.h"

#include <stdlib.h>
#include <memory>
#include <array>

#include "Item.h"

GridValidation::GridValidation(const Vector2Int& dimensions, const int scoringConsecutiveLimit)
: GridModel(dimensions)
, mScoringConsecutiveLimit(scoringConsecutiveLimit) {
}

GridValidation::~GridValidation() {
}

bool GridValidation::ValidSwap(const Vector2Int& pos_0, const Vector2Int& pos_1) {
    bool validSwap = false;
    bool adjacent = (abs(pos_1.x - pos_0.x) + abs(pos_1.y - pos_0.y) == 1);
    
    if (adjacent) {
        std::shared_ptr<Item> item_0 = GetItem(pos_0);
        std::shared_ptr<Item> item_1 = GetItem(pos_1);
        
        if ((item_0 != nullptr) && (item_1 != nullptr)) {
            Item::Type type_0 = item_0->type;
            Item::Type type_1 = item_1->type;
            bool differentTypes = (type_0 != type_1);
            
            if (differentTypes) {
                // Look for consecutive items of the same type in relevant directions
                // for both positions
                validSwap = (ValidMove(pos_0, pos_1) || ValidMove(pos_1, pos_0));
            }
        }
    }
    
    return validSwap;
}

bool GridValidation::ValidMove(Vector2Int pos_0, Vector2Int pos_1) {
    bool valid = false;
    
    Vector2Int moveDir = pos_1 - pos_0;
    
    if (moveDir.sqrMagnitude() == 1) {
        std::shared_ptr<Item> pItem_0 = GetItem(pos_0);
        Item::Type type_0 = pItem_0->type;
        int consecutive = 0;
        
        // Directional
        std::array<Item::Type, 3> directional;
        
        for (int i = 0; i <= 2; i++) {
            Vector2Int pos = pos_1 + moveDir * i;
            std::shared_ptr<Item> item = GetItem(pos);
            
            if (item != nullptr) {
                directional[i] = item->type;
            }
        }
        
        directional[0] = type_0;
        
        for (auto& type : directional) {
            if (type == type_0) {
                consecutive++;
            }
        }
        
        if (consecutive >= mScoringConsecutiveLimit) {
            valid = true;
        }
        
        // Orthogonal
        Vector2Int orthogonalDir = (moveDir.x != 0) ? Vector2Int::up : Vector2Int::right;
        
        std::array<Item::Type, 5> orthogonal;
        
        for (int i = -2; i <= 2; i++) {
            Vector2Int pos = pos_1 + orthogonalDir * i;
            std::shared_ptr<Item> item = GetItem(pos);
            
            if (item != nullptr) {
                orthogonal[i + 2] = item->type;
            }
        }
        
        orthogonal[2] = type_0;
        
        consecutive = 0;
        
        for (auto& type : orthogonal) {
            if (type == type_0) {
                consecutive++;
            }
        }
        
        if (consecutive >= mScoringConsecutiveLimit) {
            valid = true;
        }
    }
    
    return valid;
}
