#include "GridRendering.h"

#include <map>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

static std::map<Item::Type, King::Engine::Texture> TextureMap {
    { Item::TYPE_LAPIS, King::Engine::TEXTURE_BLUE },
    { Item::TYPE_EMERALD, King::Engine::TEXTURE_GREEN },
    { Item::TYPE_AMETHYST, King::Engine::TEXTURE_PURPLE },
    { Item::TYPE_RUBY, King::Engine::TEXTURE_RED },
    { Item::TYPE_TOPAZ, King::Engine::TEXTURE_YELLOW }
};

GridRendering::GridRendering(const Vector2Int& dimensions,
                             const int scoringConsecutiveLimit,
                             const std::function<void(std::vector<Item::Type>)> scoreCallback,
                             const Vector2& position,
                             const float tileSize,
                             const std::shared_ptr<King::Engine> engine)
: GridOperations(dimensions, scoringConsecutiveLimit, scoreCallback)
, mPosition(position)
, mTileSize(tileSize)
, mEngine(engine) {
}

GridRendering::~GridRendering() {
}

bool GridRendering::WithinBounds(const Vector2& pos) {
    Vector2 P0 = mPosition;
//  Vector2 P1 = P0 + mDimensions * mTileSize;
    Vector2 P1 = P0 + GetDimensions() * mTileSize;
    bool withinBounds = ((pos.x >= P0.x) && (pos.x <= P1.x) && (pos.y >= P0.y) && (pos.y <= P1.y));

    return withinBounds;
}

Vector2Int GridRendering::GridPosition(const Vector2& pos) {
    Vector2Int gridPos;
    gridPos.x = static_cast<int>((pos.x - mPosition.x) / mTileSize);
    gridPos.y = static_cast<int>((pos.y - mPosition.y) / mTileSize);

    return gridPos;
}

void GridRendering::RenderItems() {
    Vector2 dimensions = GetDimensions();
    int rows = dimensions.y;
    int cols = dimensions.x;
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            Vector2Int pos = Vector2Int { col, row };
            std::shared_ptr<Item> item = GetItem(pos);
            
            if (item != nullptr) {
                Item::Type type = item->type;
                King::Engine::Texture texture = TextureMap[type];
                float textureWidth = mEngine->GetTextureWidth(texture);
                float textureHeight = mEngine->GetTextureHeight(texture);
                float scale = item->scale;
                float x = mPosition.x + item->pos.x * mTileSize + 0.5f * (mTileSize - scale * textureWidth);
                float y = mPosition.y + item->pos.y * mTileSize + 0.5f * (mTileSize - scale * textureHeight);
                glm::mat4 matrix = glm::mat4();
                matrix = glm::translate(matrix, glm::vec3(x, y, 0));
                matrix = glm::scale(matrix, glm::vec3(scale));
                mEngine->Render(texture, matrix);
            }
        }
    }
}

void GridRendering::RenderSelection() {
    std::shared_ptr<Vector2Int> selectedPos = GetSelectedPosition();
    
    if (selectedPos != NULL) {
        King::Engine::Texture texture = King::Engine::TEXTURE_SELECTION;
        int row = selectedPos->y;
        int col = selectedPos->x;
        float textureWidth = mEngine->GetTextureWidth(texture);
        float textureHeight = mEngine->GetTextureHeight(texture);
        float x = mPosition.x + col * mTileSize + 0.5 * (mTileSize - textureWidth);
        float y = mPosition.y + row * mTileSize + 0.5 * (mTileSize - textureHeight);
        mEngine->Render(texture, x, y);
    }
}
