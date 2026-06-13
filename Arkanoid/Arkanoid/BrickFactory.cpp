#include "BrickFactory.h"
#include "BrickNorm.h"
#include "BrickIndestructible.h"
#include "BrickBonus.h"
#include "BrickSpeed.h"
#include "BrickDurability.h"

std::unique_ptr<Brick> BrickFactory::createBrick(int typeIndex, float x, float y) {
    if (typeIndex == 0) return std::make_unique<IndestructibleBrick>(x, y);
    if (typeIndex == 1) return std::make_unique<BonusBrick>(x, y);
    if (typeIndex == 2) return std::make_unique<SpeedUpBrick>(x, y);
    if (typeIndex == 3) return std::make_unique<DurabilityBrick>(x, y);
    return std::make_unique<NormalBrick>(x, y);
}
