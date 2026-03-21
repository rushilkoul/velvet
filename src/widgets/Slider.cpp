#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <velvet/widgets/Slider.hpp>

Slider::Slider(float size, float from, float to) {

    thumbBeingPressed = false;
    hovered = false;
    sliderValue = 0;
    length = size;

    active_part.setSize(sf::Vector2f(0, thickness));
    inactive_part.setSize(sf::Vector2f(size, thickness));
    thumb.setSize(sf::Vector2f(20, thickness));

    active_part.setFillColor(sf::Color(135, 135, 135));
    inactive_part.setFillColor(sf::Color(190, 190, 190));
    thumb.setFillColor(sf::Color(85, 85, 85));

    
    inactive_part.setPosition(x, y);
    active_part.setPosition(x, y);
    
    thumb.setPosition(inactive_part.getPosition());
}

void Slider::draw(sf::RenderWindow &window) {
    window.draw(inactive_part);
    window.draw(active_part);
    window.draw(thumb);
}

void Slider::update(sf::RenderWindow &window) {
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Cursor cursor;

    if (inactive_part.getGlobalBounds().contains(mousePosition)) {
        hovered = true;
    }
    else {
        hovered = false;
    }
}

void Slider::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}

void Slider::handleEvent(const sf::Event &event, sf::RenderWindow &window) {

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && hovered) {
        /*
        NOTE!!!
            all the code in the block below should be inside the changeValue() function
            but ive put it here rn cuz havnt implemented the logic for calculating slider's value yet
        */


        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2 sliderPos = inactive_part.getPosition();
        
        active_part.setSize(sf::Vector2f(mousePos.x - sliderPos.x, thickness));

        thumb.setPosition(sf::Vector2f(mousePos.x-10, thumb.getPosition().y)); // -10 cuz thats half of the thumb thickness, its hardcoded rn cuz idk man mon dieu

        changeValue(0);
    }
}

void Slider::setPosition(float x, float y) {
    inactive_part.setPosition(x, y);
    active_part.setPosition(x, y);
    thumb.setPosition(x, y);
}

sf::Vector2<float> Slider::getDimensions() {
    return sf::Vector2f(length, thickness);
}

// not implemented yet
void Slider::changeValue(float value) {
    sliderValue = value;
}