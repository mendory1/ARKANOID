#include "Field.h"
#include "Config.h"
#include "Brick.h"
#include "BrickFactory.h"

Field::Field() { initLevel(); }
void Field::initLevel() {
    bricks.clear();
    extraBottomActive = false;
    extraBottom.setSize({ WINDOW_WIDTH, 10.f });
    extraBottom.setFillColor(sf::Color::Magenta);
    extraBottom.setPosition({ 0.f, WINDOW_HEIGHT - 10.f });

    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 10; ++c) {
            float x = 2.5f + c * (BLOCK_WIDTH + BLOCK_PADDING);
            float y = 50.f + r * (BLOCK_HEIGHT + BLOCK_PADDING);
            int typeIndex = (r + c) % 5;
            bricks.push_back(BrickFactory::createBrick(typeIndex, x, y));
        }
    }
}
void Field::draw(sf::RenderWindow& window) {
    for (auto& brick : bricks) brick->draw(window);
    if (extraBottomActive) window.draw(extraBottom);
}
std::vector<std::unique_ptr<Brick>>& Field::getBricks() { return bricks; }
void Field::activateExtraBottom() { extraBottomActive = true; }
bool Field::isExtraBottomActive() const { return extraBottomActive; }
void Field::deactivateExtraBottom() { extraBottomActive = false; }
sf::FloatRect Field::getBottomBounds() const { return extraBottom.getGlobalBounds(); }
