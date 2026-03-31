#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * @brief Base class for all Velvet UI elements.
 *
 * Widget defines the minimal lifecycle used by Velvet:
 * - @ref handleEvent receives SFML events
 * - @ref render triggers internal update + draw
 * - @ref setPosition and @ref getDimensions are required for layout containers
 *
 * Custom widgets should derive from Widget and implement the internal `update`,
 * @ref setPosition, and @ref getDimensions.
 */
class Widget {
private:
    /**
     * @brief Internal per-frame update hook.
     *
     * Called by @ref render before @ref draw.
     */
    virtual void update(sf::RenderWindow &window) = 0;

    /**
     * @brief Internal draw hook.
     */
    virtual void draw(sf::RenderWindow &window);

protected:
    float x, y;

public:
    /**
     * @brief Shared font loaded by the base widget.
     */
    sf::Font font;

    /**
     * @brief Construct a widget with default font loading.
     */
    Widget();

    /**
     * @brief Handle an SFML event.
     * @param event Event propagated from @ref Window.
     * @param window Render window used for coordinate mapping.
     */
    virtual void handleEvent(const sf::Event &event, sf::RenderWindow &window);

    /**
     * @brief Render this widget.
     *
     * Default implementation calls `update(window)` then `draw(window)`.
     */
    virtual void render(sf::RenderWindow &window);

    /**
     * @brief Set top-left position of widget in window coordinates.
     */
    virtual void setPosition(float x, float y) = 0;

    /**
     * @brief Get widget dimensions used by layout containers.
     * @return Width and height.
     */
    virtual sf::Vector2<float> getDimensions() = 0;
};
