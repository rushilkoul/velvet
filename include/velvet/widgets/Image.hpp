#pragma once
#include <SFML/System/Vector2.hpp>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>

/**
 * @brief Image widget backed by SFML texture + sprite.
 */
class Image : public Widget {
private:
    sf::Sprite imageSprite;
    sf::Texture imageTexture;

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    /** @brief Render image sprite. */
    void render(sf::RenderWindow &window) override;
    /** @brief Set top-left image position. */
    void setPosition(float x, float y) override;
    /** @brief Get current rendered image dimensions. */
    sf::Vector2f getDimensions() override;

    /**
     * @brief Load image from disk.
     * @param filePath Path to image file.
     */
    Image(std::string filePath);

    /**
     * @brief Scale sprite along x/y axes.
     */
    void setScale(float scaleFactorX, float scaleFactorY);

    /**
     * @brief Set image from disk.
     * @param filePath Path to image file.
     */
    void setImage(std::string filePath);
};
