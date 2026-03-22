#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/Button.hpp>
#include <iostream>

Button::Button(float width, float height, std::string label, sf::Color borderColor, int borderThickness) : height(height), width(width) {
    x = 0;
    y = 0;
    hovered = false;
    clicked = false;

    primaryColor = sf::Color(164, 71, 251);
    hoverColor = sf::Color::Yellow;
    clickColor = sf::Color::Red;

    if (!defaultTexture.loadFromFile("src/assets/btn.png")) {
        std::cerr << "Warning: failed to load texture src/assets/btn.png" << std::endl;
    }
    sprite.setTexture(defaultTexture);

    sprite.setPosition(x, y);

    //shape.setSize(sf::Vector2f(width, height));
    //shape.setPosition(x, y);
    //shape.setFillColor(primaryColor);

    /*
    if(borderThickness != 0 && borderThickness > 0) {
        shape.setOutlineColor(borderColor);
        shape.setOutlineThickness(borderThickness);
    }
    */

    // ---logic resizing the sprite---
    sf::Vector2u textureSize = defaultTexture.getSize();

    float scaleFactorX = width / textureSize.x;
    float scaleFactorY = height / textureSize.y;

    sprite.setScale(scaleFactorX, scaleFactorY);

    if (!font.loadFromFile("src/assets/AdwaitaSans-Regular.ttf")) {
        std::cerr << "Warning: failed to load font src/assets/AdwaitaSans-Regular.ttf" << std::endl;
    }

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);



    // setting origin of text to its center
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    text.setPosition(x + width / 2.0f, y + height / 2.0f);

    /*
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    text.setPosition(x + width / 2.0f, y + height / 2.0f);
    */
}

Button::Button(const Button& other)
    : Widget(other),
      defaultTexture(other.defaultTexture),
      hoverTexture(other.hoverTexture),
      clickTexture(other.clickTexture),
      sprite(other.sprite),
      text(other.text),
      primaryColor(other.primaryColor),
      hoverColor(other.hoverColor),
      clickColor(other.clickColor),
      borderColor(other.borderColor),
      borderThickness(other.borderThickness),
      hovered(other.hovered),
      clicked(other.clicked)
{
    // reassign font pointer to THIS object's font
    text.setFont(font);
    sprite.setTexture(defaultTexture);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(text);
}

void Button::update(sf::RenderWindow &window) {
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Cursor cursor;

    // checking if mouse is hovering the button
    if (sprite.getGlobalBounds().contains(mousePosition)) {
        //shape.setFillColor(hoverColor);

        if (cursor.loadFromSystem(sf::Cursor::Hand)) window.setMouseCursor(cursor);
        hovered = true;
    }
    else {
        //shape.setFillColor(primaryColor);
        hovered = false;
    }

    /*
    if (clicked) shape.setFillColor(clickColor);
    else if (hovered) shape.setFillColor(hoverColor);
    else shape.setFillColor(primaryColor);
    */
}

void Button::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void Button::handleEvent(const sf::Event &event, sf::RenderWindow &window) {
    if (hovered && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        clicked = true;
        if (onclick) onclick();
    }
    else {
        clicked = false;
    }
}

void Button::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

sf::Vector2<float> Button::getDimensions() {
    return sf::Vector2f(width, height);
}