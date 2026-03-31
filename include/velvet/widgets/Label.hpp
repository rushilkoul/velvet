#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <variant>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>

/**
 * @brief Text display widget with simple style map support.
 *
 * Supported style keys (`std::unordered_map<std::string, std::variant<unsigned int, float, std::string>>`):
 * - `fontPath` (`std::string`)
 * - `fontSize` (`float`)
 * - `lineSpacing` (`float`)
 * - `letterSpacing` (`float`)
 * - `fillColor` (`unsigned int`, RGBA hex like `0xRRGGBBAA`)
 * - `outlineColor` (`unsigned int`)
 * - `outlineThickness` (`float`)
 * - `fontStyle` (`std::string`: `regular|bold|italic|underlined|strikethrough`)
 * - `backgroundColor` (`unsigned int`)
 */
class Label : public Widget {
private:
    sf::Text LText;
    sf::Font font;
    sf::RectangleShape backgroundShape;

    std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styles = {
        {"fontPath", "src/assets/AdwaitaSans-Regular.ttf"},
        {"fontSize", 20.f},
        {"lineSpacing", 1.f},
        {"letterSpacing", 1.f},
        {"fillColor", 0x000000FFu},
        {"outlineColor", 0xFFFFFFFFu},
        {"outlineThickness", 0.f},
        {"fontStyle", "regular"},
        {"backgroundColor", 0x00000000u}
    };

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    /** @brief Render the label. */
    void render(sf::RenderWindow &window) override;

    /** @brief Set top-left position of label text/background. */
    void setPosition(float x, float y) override;

    /** @brief Get current text bounds. */
    sf::Vector2f getDimensions() override;

    /**
     * @brief Create label with text and optional style overrides.
     */
    Label(std::string text, std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling = {});

    /**
     * @brief Replace displayed string.
     */
    void setText(const std::string txt);

    /**
     * @brief Apply/override style properties.
     *
     * Unknown keys are ignored with a warning.
     */
    void overrideStyling(std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling);
};
