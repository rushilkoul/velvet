#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Widget {
private:
    virtual void update(sf::RenderWindow &window) = 0; // make this an abstract class
    virtual void draw(sf::RenderWindow &window);

protected:
    float x, y;

public:
    sf::Font font;
    Widget();
    virtual void handleEvent(const sf::Event &event);
    virtual void render(sf::RenderWindow &window);
    virtual void setPosition(float x, float y) = 0;
    virtual sf::Vector2<float> getBounds() = 0;
};
