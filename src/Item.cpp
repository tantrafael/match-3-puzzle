#include "Item.h"

Item::Item()
: type(Item::TYPE_MAX)
, pos(Vector2::zero)
, scale(1.0f) {
};

Item::~Item() {
}
