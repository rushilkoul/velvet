#include <velvet/base/Widget.hpp>

Widget::Widget() {
    font.loadFromFile("src/assets/AdwaitaSans-Regular.ttf");
}

void Widget::draw(sf::RenderWindow &window) {}

void Widget::handleEvent(const sf::Event &event, sf::RenderWindow &window) {}

void Widget::render(sf::RenderWindow &window) {
    update(window);
    draw(window);
}