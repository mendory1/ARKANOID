#pragma once
#include <vector>
#include <memory>
#include "Brick.h"

class Field {
private:
    std::vector<std::unique_ptr<Brick>> bricks;
    sf::RectangleShape extraBottom;
    bool extraBottomActive;
public:
    Field();
    void initLevel();
    void draw(sf::RenderWindow& window);
    std::vector<std::unique_ptr<Brick>>& getBricks() { return bricks; }

    void activateExtraBottom() { extraBottomActive = true; }
    bool isExtraBottomActive() const { return extraBottomActive; }
    void deactivateExtraBottom() { extraBottomActive = false; }
    sf::FloatRect getBottomBounds() const { return extraBottom.getGlobalBounds(); }
};
