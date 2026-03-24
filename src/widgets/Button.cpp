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

    std::string texturePath = "src/assets/btn.png";
    if (!defaultTexture.loadFromFile(texturePath)) {
        std::cerr << "\033[33m[Warning] (Button) Failed to load texture: '" << texturePath << "'\033[0m" << std::endl;
    }

    sprite.setTexture(defaultTexture);
    sprite.setPosition(x, y);

    // ---logic for resizing the sprite---
    sf::Vector2u textureSize = defaultTexture.getSize();

    float scaleFactorX = width / textureSize.x;
    float scaleFactorY = height / textureSize.y;

    sprite.setScale(scaleFactorX, scaleFactorY);

    std::string fontPath = "src/assets/AdwaitaSans-Regular.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "\033[33m[Warning] (Button) Failed to load font: '" << fontPath << "'\033[0m" << std::endl;
    }

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);

    // setting origin of text to its center
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    text.setPosition(x + width / 2.0f, y + height / 2.0f);
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
        if (cursor.loadFromSystem(sf::Cursor::Hand)) window.setMouseCursor(cursor);
        hovered = true;
    }
    else {
        hovered = false;
    }
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
