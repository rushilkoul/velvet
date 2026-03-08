#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/HStack.hpp>
#include <iostream>

HStack::HStack(float gap) : gap(gap) {}

void HStack::draw(sf::RenderWindow &window) {
    for (Widget* child : children) {
        child->render(window);
    }
}

void HStack::update(sf::RenderWindow &window) {
    float x_pos = xPos;
    float y_pos = yPos;

    for (Widget* child : children) {
        child->setPosition(x_pos, y_pos);

        sf::Vector2f dims = child->getDimensions();
        x_pos += dims.x;
    }
}

void HStack::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void HStack::add(Widget* widget) {
    children.push_back(widget);
}

void HStack::setPosition(float x, float y) {
    xPos = x;
    yPos = y;
}

sf::Vector2f HStack::getDimensions() {
    float height = 0;
    float width = 0;
    for (Widget* child : children) {
        sf::Vector2f childDims = child->getDimensions();

        width += childDims.x;

        if (height < childDims.y) {
            height = childDims.y;
        }
    }

    return sf::Vector2f(width, height);
}