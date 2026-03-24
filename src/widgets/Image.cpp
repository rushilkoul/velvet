#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/Image.hpp>
#include <iostream>

Image::Image(std::string filePath) {
    if (!imageTexture.loadFromFile(filePath)) {
        // TODO: implement error
        std::cerr << "\033[33m[Warning] (Image) Failed to load image: '" << filePath << "'\033[0m" << std::endl;
    }

    imageSprite.setTexture(imageTexture);
}

void Image::draw(sf::RenderWindow &window) {
    window.draw(imageSprite);
}

void Image::update(sf::RenderWindow &window) {
    
}

void Image::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void Image::setPosition(float x, float y) {
    imageSprite.setPosition(x, y);
}

sf::Vector2f Image::getDimensions() {
    sf::FloatRect textBounds = imageSprite.getGlobalBounds();

    return sf::Vector2f(textBounds.width, textBounds.height);
}

void Image::setScale(float scaleFactorX, float scaleFactorY) {
    imageSprite.setScale(scaleFactorX, scaleFactorY);
}
