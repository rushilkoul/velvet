#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/Label.hpp>
#include <iostream>

Label::Label(std::string text, int fontSize) {
    if (!font.loadFromFile("src/assets/space-grotesk.ttf")) {
        std::cerr << "Warning: failed to load font src/assets/space-grotesk.ttf" << std::endl;
    }

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
void Label::setText(const std::string txt) {
    LText.setString(txt);
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


    return sf::Vector2f(textBounds.width + textBounds.left, textBounds.height + textBounds.top);
}