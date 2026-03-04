#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <velvet/widgets/Button.hpp>
#include <iostream>

Button::Button(float x, float y, float width, float height, std::string label, sf::Color borderColor, int borderThickness) {
    hovered = false;
    clicked = false;

    primaryColor = sf::Color(164, 71, 251);
    hoverColor = sf::Color::Yellow;
    clickColor = sf::Color::Red;


    shape.setSize(sf::Vector2f(width, height));

    shape.setPosition(x, y);
    shape.setFillColor(primaryColor);

    if(borderThickness != 0 && borderThickness > 0) {
        shape.setOutlineColor(borderColor);
        shape.setOutlineThickness(borderThickness);
    }

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}

void Button::update(sf::RenderWindow &window) {
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Cursor cursor;

    // checking if mouse is hovering the button
    if (shape.getGlobalBounds().contains(mousePosition)) {
        shape.setFillColor(hoverColor);

        if (cursor.loadFromSystem(sf::Cursor::Hand)) window.setMouseCursor(cursor);
        hovered = true;
    }
    else {
        shape.setFillColor(primaryColor);
        hovered = false;
    }

    // clickkk
    if (clicked) shape.setFillColor(clickColor);
    else if (hovered) shape.setFillColor(hoverColor);
    else shape.setFillColor(primaryColor);

}

void Button::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void Button::handleEvent(const sf::Event &event) {
    if (hovered && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        clicked = true;
        std::cout << std::endl << "clicked button!" << std::endl;
    }
    else {
        clicked = false;
    }
}
