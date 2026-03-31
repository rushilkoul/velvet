#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <functional>
#include <unordered_map>
#include <variant>

/**
 * @brief Clickable button widget with text label.
 *
 * Assign a lambda to @ref onclick to react to left-click presses.
 *
 * Supported style keys (`std::unordered_map<std::string, std::variant<unsigned int, float, std::string>>`):
 * - `fontPath` (`std::string`)
 * - `fontSize` (`float`)
 * - `letterSpacing` (`float`)
 * - `fontColor` (`unsigned int`, RGBA hex like `0xRRGGBBAA`)
 * - `hoverFontColor` (`unsigned int`)
 * - `outlineColor` (`unsigned int`)
 * - `outlineThickness` (`float`)
 * - `backgroundColor` (`unsigned int`)
 * - `hoverBackgroundColor` (`unsigned int`)
 * - `width` (`float`)
 * - `height` (`float`)
 */
class Button : public Widget {

    sf::Sprite sprite;
    sf::Text text;
    sf::RectangleShape shape;
    sf::Font font;

    std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styles = {
        {"fontPath", "src/assets/AdwaitaSans-Regular.ttf"},
        {"fontSize", 20.f},
        {"letterSpacing", 1.f},
        {"fontColor", 0x000000FFu},
        {"hoverFontColor", 0x000000FFu},
        {"outlineColor", 0x000000FFu},
        {"outlineThickness", 1.f},
        {"backgroundColor", 0xFFFFFFFFu},
        {"hoverBackgroundColor", 0xEEEEEEFFu},
        {"width", 200.f},
        {"height", 50.f}
    };

    bool hovered;
    bool clicked;

    float width, height;

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    /**
     * @brief Called when the button is pressed with left mouse button while hovered.
     */
    std::function<void()> onclick;
    
    /** @brief Render the button. */
    void render(sf::RenderWindow &window) override;
    /** @brief Process hover/press input events. */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

    /**
     * @brief Create a button.
     * @param width Button width in pixels.
     * @param height Button height in pixels.
     * @param label Text displayed in the center.
     * @param borderColor Reserved for future border styling.
     * @param borderThickness Reserved for future border styling.
     */
    Button(std::string label, std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling = {});

    /** @brief Copy constructor. */
    Button(const Button& other);

    /** @brief Set top-left position of the button. */
    void setPosition(float x, float y) override;

    /** @brief Get button dimensions. */
    sf::Vector2<float> getDimensions() override;

    /**
     * @brief Apply/override style properties.
     *
     * Unknown keys are ignored with a warning.
     */
    void overrideStyling(std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling);
};
