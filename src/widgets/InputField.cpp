#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <velvet/widgets/InputField.hpp>
#include <iostream>

InputField::InputField(std::string placeholder, std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling) : placeholder(placeholder) {
    std::string fontPath = "src/assets/AdwaitaSans-Regular.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "\033[33m[Warning] (InputField) Failed to load font: '" << fontPath << "'\033[0m" << std::endl;
    }

    textField.setFont(font);
    textField.setPosition(x, y);
    textField.setString(" ");

    placeholderText.setFont(font);

    container.setPosition(x, y);
    container.setOutlineThickness(1.5);

    overrideStyling(styling);

    sf::FloatRect bounds = textField.getLocalBounds();
    float containerWidth = std::get<float>(styles.at("width"));

    container.setSize(sf::Vector2f(containerWidth, bounds.height + bounds.top + 10));
}

void InputField::draw(sf::RenderWindow &window) {
    window.draw(container);

    sf::View ogView = window.getView();
    sf::Vector2u winSize = window.getSize();
    sf::FloatRect containerBounds = container.getGlobalBounds();

    sf::View clipView;
    clipView.setViewport(sf::FloatRect(
        containerBounds.left / winSize.x,
        containerBounds.top / winSize.y,
        containerBounds.width / winSize.x,
        containerBounds.height / winSize.y
    ));

    clipView.setSize(containerBounds.width, containerBounds.height);

    float padding  = 6.f;
    float textW    = textField.getLocalBounds().width;
    float visibleW = containerBounds.width - padding * 2;

    float scrollX = (textW > visibleW)
                  ? containerBounds.left + padding + textW - visibleW / 2.f
                  : containerBounds.left + containerBounds.width / 2.f;

    clipView.setCenter(scrollX, containerBounds.top + containerBounds.height / 2.f);

    window.setView(clipView);

    window.draw(textField);

    if (content.empty()) {
        window.draw(placeholderText);
    }

    window.setView(ogView);
}

void InputField::update(sf::RenderWindow &window) {
    textField.setString(content);
    placeholderText.setString(placeholder);
}


void InputField::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void InputField::setPosition(float x, float y) {
    container.setPosition(x, y);
    textField.setPosition(x, y);
    placeholderText.setPosition(x, y);
}

sf::Vector2f InputField::getDimensions() {
    sf::FloatRect bgBounds =  container.getLocalBounds();
    return sf::Vector2f(bgBounds.width + bgBounds.left, bgBounds.height + bgBounds.top);
}

void InputField::handleEvent(const sf::Event &event, sf::RenderWindow &window) {
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && container.getGlobalBounds().contains(mousePosition)) {
        focused = true;
        container.setOutlineColor(sf::Color(80, 140, 255));
        container.setOutlineThickness(3);
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !container.getGlobalBounds().contains(mousePosition)) {
        focused = false;
        container.setOutlineColor(sf::Color(90, 90, 90));
        container.setOutlineThickness(1.5);
    }

    if (event.type == sf::Event::TextEntered && focused) {
        if (std::isprint(event.text.unicode))
            content += event.text.unicode;
    }
    else if (event.type == sf::Event::KeyPressed && focused) {
        if (event.key.code == sf::Keyboard::BackSpace && !content.empty()) {
            content.pop_back();
        }
    }
}

void InputField::overrideStyling(std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling) {

    for (auto& [key, val] : styling) {
        if(styles.contains(key)) {
            styles[key] = val;
        }
        else {
        std::cerr << "\033[33m[Warning] (InputField) Invalid style property: '" << key << "'\033[0m" << std::endl;
       }
    }

    std::string customFontPath;
    customFontPath = std::get<std::string>(styles.at("fontPath"));
    if (!font.loadFromFile(customFontPath)) {
        std::cerr << "\033[33m[Warning] (InputField) Failed to load font: '" << customFontPath << "'\033[0m" << std::endl;
    }    

    container.setFillColor(sf::Color(std::get<unsigned int>(styles.at("backgroundColor"))));
    container.setOutlineColor(sf::Color(std::get<unsigned int>(styles.at("outlineColor"))));

    textField.setCharacterSize(std::get<float>(styles.at("fontSize")));
    textField.setLetterSpacing(std::get<float>(styles.at("letterSpacing")));
    textField.setFillColor(sf::Color(std::get<unsigned int>(styles.at("fontColor"))));

    placeholderText.setCharacterSize(std::get<float>(styles.at("fontSize")));
    placeholderText.setLetterSpacing(std::get<float>(styles.at("letterSpacing")));
    placeholderText.setFillColor(sf::Color(std::get<unsigned int>(styles.at("placeholderColor"))));
}

std::string InputField::getContent() {
    return content;
}

std::string InputField::getPlaceholder() {
    return placeholder;
}

void InputField::setPlaceholder(std::string placeholderString) {
    placeholder = placeholderString;
}
