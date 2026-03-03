#include <velvet/core/Widget.hpp>

void Widget::draw(sf::RenderWindow &window) {}

void Widget::handleEvent(const sf::Event &event) {}

void Widget::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}
