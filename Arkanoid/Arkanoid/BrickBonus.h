#pragma once
#include "Brick.h"

class BonusBrick : public Brick {
public:
    BonusBrick(float x, float y);
    void hit(int& score, Game& game) override;
};
