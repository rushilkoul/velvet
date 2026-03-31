#pragma once
#include <SFML/System/Vector2.hpp>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <functional>

/**
 * @brief Clickable button widget with text label.
 *
 * Assign a lambda to @ref onclick to react to left-click presses.
 */
class Button : public Widget {
    sf::Texture defaultTexture;
    sf::Texture hoverTexture;
    sf::Texture clickTexture;

    sf::Sprite sprite;
    sf::Text text;

    sf::Color primaryColor;
    sf::Color hoverColor;
    sf::Color clickColor;
    sf::Color borderColor;
    
    int borderThickness;

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
    Button(float width=100, float height=50, std::string label="button", sf::Color borderColor = sf::Color::White, int borderThickness = 0);

    /** @brief Copy constructor. */
    Button(const Button& other);

    /** @brief Set top-left position of the button. */
    void setPosition(float x, float y) override;

    /** @brief Get button dimensions. */
    sf::Vector2<float> getDimensions() override;
};
