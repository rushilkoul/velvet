#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/VStack.hpp>
#include <iostream>

VStack::VStack(float gap) : gap(gap) {}

void VStack::draw(sf::RenderWindow &window) {
    for (Widget* child : children) {
        child->render(window);
    }
}

void VStack::update(sf::RenderWindow &window) {
    float x_pos = xPos;
    float y_pos = yPos;

    for (Widget* child : children) {
        child->setPosition(x_pos, y_pos);

        sf::Vector2f dims = child->getDimensions();
        y_pos += dims.y + gap;
    }
}

void VStack::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void VStack::add(Widget* widget) {
    children.push_back(widget);
}

void VStack::setPosition(float x, float y) {
    xPos = x;
    yPos = y;
}

sf::Vector2f VStack::getDimensions() {
    float height = 0;
    float width = 0;

    for (Widget* child : children) {
        sf::Vector2f childDims = child->getDimensions();

        height += childDims.y + gap;

        if (width < childDims.x) {
            width = childDims.x;
        }
    }
    height -= gap;
    
    return sf::Vector2f(width, height);
}