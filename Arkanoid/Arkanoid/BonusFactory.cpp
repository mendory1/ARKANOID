#include "BonusFactory.h"
#include "BonusWide.h"
#include "BonusBottom.h"
#include "BonusBall.h"
#include "Functions.h"

std::unique_ptr<Bonus> BonusFactory::createRandomBonus(sf::Vector2f pos) {
    int r = getRandomNumber(0, 2);
    if (r == 0) return std::make_unique<BonusWide>(pos);
    if (r == 1) return std::make_unique<BonusBottom>(pos);
    return std::make_unique<BonusBall>(pos);
}
