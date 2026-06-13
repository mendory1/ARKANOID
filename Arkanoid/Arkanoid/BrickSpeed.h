#pragma once
#include "Brick.h"

class SpeedUpBrick : public Brick {
public:
    SpeedUpBrick(float x, float y);
    void hit(int& score, Game& game) override;
};
