#pragma once
#include <SFML/Graphics.hpp>
#include <velvet/base/Widget.hpp>
#include <vector>

class Window {
    sf::RenderWindow window;
    sf::Color backgroundColor;
    std::vector<Widget*> widgets;
    
    void add_widget(Widget* w) { add(w); }
    void add_widget(Widget& w) { add(&w); }

public:
    Window(int width, int height, const std::string& title)
        : window(sf::VideoMode(width, height), title),
          backgroundColor(sf::Color(230, 230, 230)) {
            window.setFramerateLimit(60);
          }

    void setBackgroundColor(sf::Color color) { backgroundColor = color; }

    void add(Widget* widget) { widgets.push_back(widget); }

    template<typename... Ts>
    void add(Ts&&... widgets_list) {
        (add_widget(std::forward<Ts>(widgets_list)), ...);
    }

    bool isOpen() { return window.isOpen(); }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            sf::Cursor cursor;

            while (window.pollEvent(event)) {
                if (cursor.loadFromSystem(sf::Cursor::Arrow)) window.setMouseCursor(cursor);
                
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::Resized) {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                }

                for (Widget* w : widgets)
                    w->handleEvent(event, window);
            }
            window.clear(backgroundColor);

            for (Widget* w : widgets)
                w->render(window);

            window.display();
        }
    }
};
