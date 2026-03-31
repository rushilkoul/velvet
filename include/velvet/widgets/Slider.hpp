#pragma once
#include <SFML/System/Vector2.hpp>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <functional>

/**
 * @brief Horizontal draggable slider widget.
 *
 * Emits value changes via @ref onchange while the thumb is dragged.
 */
class Slider : public Widget {
private:
    sf::RectangleShape active_part;
    sf::RectangleShape inactive_part;
    sf::RectangleShape thumb;

    float height, width;
    float from, to;
    float sliderValue;
    float thickness = 20;
    float length;

    bool thumbBeingPressed;
    bool hovered;

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    /**
     * @brief Callback fired when value changes during dragging.
     */
    std::function<void(float)> onchange;

    /** @brief Render the slider. */
    void render(sf::RenderWindow &window) override;
    /** @brief Handle mouse press/release/move input for dragging. */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;
    /** @brief Set top-left position of slider track. */
    void setPosition(float x, float y) override;
    /** @brief Get slider dimensions (`length` x `thickness`). */
    sf::Vector2f getDimensions() override;

    /**
     * @brief Create slider.
     * @param size Track length in pixels.
     * @param from Minimum value.
     * @param to Maximum value.
     */
    Slider(float size, float from = 0.0f, float to = 1.0f);

    /** @brief Set internal value (no callback triggered). */
    void changeValue(float value);

    /** @brief Read current value. */
    float getValue();
};
