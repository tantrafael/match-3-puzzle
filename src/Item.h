#pragma once

#include "Vector2.h"

struct Item {
    enum Type {
        TYPE_LAPIS,
        TYPE_EMERALD,
        TYPE_AMETHYST,
        TYPE_RUBY,
        TYPE_TOPAZ,
        TYPE_MAX
    };

    Type type;
    Vector2 pos;
    float scale;

    Item();
    Item(Type type);
    Item(Type type, Vector2 pos);
    ~Item();
};
