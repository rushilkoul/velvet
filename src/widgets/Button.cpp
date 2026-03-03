#include <velvet/widgets/Button.hpp>

Button::Button(float x, float y, float width, float height, std::string label){
    shape.setSize(sf::Vector2f(width, height));

    shape.setPosition(x, y);
    shape.setFillColor(sf::Color(164, 77, 251));

    // shape.setOutlineColor(sf::Color::White);
    // shape.setOutlineThickness(2);

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");
    }

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color(255, 255, 255));

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(text);
}

void Button::update(sf::RenderWindow &window) {
}

void Button::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void Button::handleEvent(const sf::Event &event) {
}
