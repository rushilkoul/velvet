#pragma once
#include <SFML/Graphics.hpp>

class Widget {
private:
    virtual void update(sf::RenderWindow &window) = 0; // make this an abstract class
    virtual void draw(sf::RenderWindow &window);
public:
    virtual void handleEvent(const sf::Event &event);
    virtual void render(sf::RenderWindow &window);
};
