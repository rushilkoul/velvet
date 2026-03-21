#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/Label.hpp>
#include <iostream>

Label::Label(std::string text, int fontSize) {
    font.loadFromFile("src/assets/arial.ttf");

    LText.setFont(font);
    LText.setString(text);
    LText.setCharacterSize(fontSize);
    LText.setFillColor(sf::Color::Black);

    LText.setPosition(x, y);
}

void Label::draw(sf::RenderWindow &window) {
    window.draw(LText);
}

void Label::update(sf::RenderWindow &window) {
    
}

void Label::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void Label::setPosition(float x, float y) {
    LText.setPosition(x, y);
}

sf::Vector2f Label::getDimensions() {
    sf::FloatRect textBounds = LText.getLocalBounds();

    return sf::Vector2f(textBounds.width, textBounds.height);
}