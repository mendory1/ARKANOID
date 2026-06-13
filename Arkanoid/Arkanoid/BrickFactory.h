#pragma once
#include <memory>

class Brick;

class BrickFactory {
public:
    static std::unique_ptr<Brick> createBrick(int typeIndex, float x, float y);
};
