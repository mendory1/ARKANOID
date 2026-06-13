#pragma once
#include "Brick.h"

class IndestructibleBrick : public Brick {
public:
    IndestructibleBrick(float x, float y);
    void hit(int& score, Game& game) override;

    bool isRequiredForWin() const override { return false; }
};
