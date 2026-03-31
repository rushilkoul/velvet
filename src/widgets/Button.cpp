#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/Button.hpp>
#include <iostream>

Button::Button(float width,
               float height,
               std::string label,
               std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling,
               unsigned int borderColor,
               float borderThickness) {
    x = 0;
    y = 0;
    hovered = false;
    clicked = false;

    styling["width"] = width;
    styling["height"] = height;
    styling["outlineColor"] = borderColor;
    styling["outlineThickness"] = borderThickness;

    overrideStyling(styling);

    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(this->width, this->height));

    text.setString(label);

    // setting origin of text to its center
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

    text.setPosition(x + this->width / 2.0f, y + this->height / 2.0f);
}

Button::Button(const Button& other)
    : Widget(other),
      shape(other.shape),
      text(other.text),
      styles(other.styles),
      hovered(other.hovered),
      clicked(other.clicked)
{
    // reassign font pointer to THIS object's font
    text.setFont(font);
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
        if (cursor.loadFromSystem(sf::Cursor::Hand)) window.setMouseCursor(cursor);

        text.setFillColor(sf::Color(std::get<unsigned int>(styles.at("hoverFontColor"))));
        shape.setFillColor(sf::Color(std::get<unsigned int>(styles.at("hoverBackgroundColor"))));

        hovered = true;
    }
    else {
        text.setFillColor(sf::Color(std::get<unsigned int>(styles.at("fontColor"))));
        shape.setFillColor(sf::Color(std::get<unsigned int>(styles.at("backgroundColor"))));

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
    shape.setPosition(x, y);
    text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

sf::Vector2<float> Button::getDimensions() {
    return sf::Vector2f(width, height);
}

void Button::overrideStyling(std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling) {

    for (auto& [key, val] : styling) {
        if(styles.contains(key)) {
            styles[key] = val;
        }
        else {
        std::cerr << "\033[33m[Warning] (Button) Invalid style property: '" << key << "'\033[0m" << std::endl;
       }
    }

    std::string customFontPath;
    customFontPath = std::get<std::string>(styles.at("fontPath"));
    if (!font.loadFromFile(customFontPath)) {
        std::cerr << "\033[33m[Warning] (Button) Failed to load font: '" << customFontPath << "'\033[0m" << std::endl;
    }

    width = std::get<float>(styles.at("width"));
    height = std::get<float>(styles.at("height"));

    shape.setFillColor(sf::Color(std::get<unsigned int>(styles.at("backgroundColor"))));
    shape.setOutlineColor(sf::Color(std::get<unsigned int>(styles.at("outlineColor"))));
    shape.setOutlineThickness(std::get<float>(styles.at("outlineThickness")));

    text.setFont(font);
    text.setCharacterSize(std::get<float>(styles.at("fontSize")));
    text.setLetterSpacing(std::get<float>(styles.at("letterSpacing")));
    text.setFillColor(sf::Color(std::get<unsigned int>(styles.at("fontColor"))));
}
