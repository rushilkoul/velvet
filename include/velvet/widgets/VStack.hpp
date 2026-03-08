#pragma once
#include <velvet/base/Widget.hpp>
#include <velvet/base/Window.hpp>
#include <vector>

class VStack : public Widget {
private:
    float xPos = 0;
    float yPos = 0;
    //float height = 0;
    //float width = 0;

    std::vector<Widget *> children;

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    float gap;

    void render(sf::RenderWindow &window);
    void add(Widget* widget);
    void setPosition(float x, float y) override;
    sf::Vector2f getDimensions() override;
    VStack(float gap=0);

};
