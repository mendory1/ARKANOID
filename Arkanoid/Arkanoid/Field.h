#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Brick;

class Field {
private:
    std::vector<std::unique_ptr<Brick>> bricks;
    sf::RectangleShape extraBottom;
    bool extraBottomActive;
public:
    Field();
    void initLevel();
    void draw(sf::RenderWindow& window);
    std::vector<std::unique_ptr<Brick>>& getBricks();

    void activateExtraBottom();
    bool isExtraBottomActive() const;
    void deactivateExtraBottom();
    sf::FloatRect getBottomBounds() const;
};
