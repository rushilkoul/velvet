#include <velvet/base/Widget.hpp>

Widget::Widget() {
    font.loadFromFile("src/assets/space-grotesk.ttf");
}

void Widget::draw(sf::RenderWindow &window) {}

void Widget::handleEvent(const sf::Event &event) {}

void Widget::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}