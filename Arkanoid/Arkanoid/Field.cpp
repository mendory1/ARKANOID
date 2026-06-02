#include "Field.h"
#include "Config.h"

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
            BlockType t = static_cast<BlockType>((r + c) % 5);
            bricks.push_back(std::make_unique<Brick>(x, y, t));
        }
    }
}
void Field::draw(sf::RenderWindow& window) {
    for (auto& brick : bricks) brick->draw(window);
    if (extraBottomActive) window.draw(extraBottom);
}
