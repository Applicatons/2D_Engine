#pragma once
#include <pch.h>

// oh yeah big brain time
class tile;

// user interactable tile
class itile {
public:
    itile() : parent(nullptr) {}
    itile(tile* parent, int index) : parent(parent), index(index) {}

    tile* get_parent() {
        return this->parent;
    }
private:
    tile* parent;
    int index;
};