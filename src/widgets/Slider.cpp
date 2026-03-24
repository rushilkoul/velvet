#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <velvet/widgets/Slider.hpp>

Slider::Slider(float size, float from, float to) : from(from), to(to) {

    thumbBeingPressed = false;
    hovered = false;
    sliderValue = from;
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
    
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && hovered)
        thumbBeingPressed = true;

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        thumbBeingPressed = false;


    if (thumbBeingPressed && event.type == sf::Event::MouseMoved) {

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Vector2 sliderPos = inactive_part.getPosition();
        
        float minX = sliderPos.x;
        float maxX = sliderPos.x + length - 10;  // -10 for thumb width
        float clampedX = std::max(minX, std::min(mousePos.x - 10, maxX));
        
        active_part.setSize(sf::Vector2f(clampedX - sliderPos.x + 10, thickness));
        thumb.setPosition(sf::Vector2f(clampedX, thumb.getPosition().y));

        float value = from + (clampedX - minX) / (maxX - minX) * (to - from); /// ugly but works shh
        changeValue(value);
        if (onchange) onchange(value);
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

void Slider::changeValue(float value) {
    sliderValue = value;
}

float Slider::getValue() {
    return sliderValue;
}
