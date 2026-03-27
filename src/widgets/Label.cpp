#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/Label.hpp>
#include <iostream>

Label::Label(std::string text, std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling) {
    std::string fontPath = "src/assets/AdwaitaSans-Regular.ttf";
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "\033[33m[Warning] (Label) Failed to load font: '" << fontPath << "'\033[0m" << std::endl;
    }

    LText.setFont(font);
    LText.setString(text);

    // setting the styles
    overrideStyling(styling);

    LText.setPosition(x, y);

    backgroundShape.setPosition(x, y);
    backgroundShape.setSize(getDimensions());
}

void Label::draw(sf::RenderWindow &window) {
    window.draw(backgroundShape);
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
    backgroundShape.setPosition(x, y);
    LText.setPosition(x, y);
}

sf::Vector2f Label::getDimensions() {
    sf::FloatRect textBounds = LText.getLocalBounds();


    return sf::Vector2f(textBounds.width + textBounds.left, textBounds.height + textBounds.top);
}

void Label::overrideStyling(std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling) {

    for (auto& [key, val] : styling) {
        if(styles.contains(key)) {
            styles[key] = val;
        }
        else {
        std::cerr << "\033[33m[Warning] (Label) Invalid style property: '" << key << "'\033[0m" << std::endl;
       }
    }

    std::string customFontPath;
    customFontPath = std::get<std::string>(styles.at("fontPath"));
    if (!font.loadFromFile(customFontPath)) {
        std::cerr << "\033[33m[Warning] (Label) Failed to load font: '" << customFontPath << "'\033[0m" << std::endl;
    }

    std::string textStyle;
    textStyle = std::get<std::string>(styles.at("fontStyle"));
    std::transform(textStyle.begin(), textStyle.end(), textStyle.begin(), ::tolower);

    if (textStyle == "regular") {
        LText.setStyle(sf::Text::Regular);
    }
    else if (textStyle == "bold") {
        LText.setStyle(sf::Text::Bold);
    }
    else if (textStyle == "strikethrough") {
        LText.setStyle(sf::Text::StrikeThrough);
    }
    else if (textStyle == "underlined") {
        LText.setStyle(sf::Text::Underlined);
    }
    else if (textStyle == "italic") {
        LText.setStyle(sf::Text::Italic);
    }
    else {
        std::cerr << "\033[33m[Warning] (Label) Invalid font style: '" << textStyle << "'\033[0m" << std::endl;
    }

    backgroundShape.setFillColor(sf::Color(std::get<unsigned int>(styles.at("backgroundColor"))));

    LText.setCharacterSize(std::get<float>(styles.at("fontSize")));
    LText.setLineSpacing(std::get<float>(styles.at("lineSpacing")));
    LText.setLetterSpacing(std::get<float>(styles.at("letterSpacing")));
    LText.setFillColor(sf::Color(std::get<unsigned int>(styles.at("fillColor"))));
    LText.setOutlineColor(sf::Color(std::get<unsigned int>(styles.at("outlineColor"))));
    LText.setOutlineThickness(std::get<float>(styles.at("outlineThickness")));
}
