#pragma once
#include <SFML/Graphics.hpp>
#include <velvet/base/Widget.hpp>
#include <vector>

/**
 * @brief Application window and main event/render loop.
 *
 * `Window` owns the SFML `RenderWindow`, forwards events to added widgets,
 * and renders widgets each frame.
 *
 * Typical usage:
 * @code{.cpp}
 * Window window(800, 600, "My App");
 * window.add(rootWidget);
 * window.run();
 * @endcode
 */
class Window {
    sf::RenderWindow window;
    sf::Color backgroundColor;
    std::vector<Widget*> widgets;
    
    void add_widget(Widget* w) { add(w); }
    void add_widget(Widget& w) { add(&w); }

public:
        /**
         * @brief Create a window.
         */
    Window(int width, int height, const std::string& title)
        : window(sf::VideoMode(width, height), title),
          backgroundColor(sf::Color(230, 230, 230)) {
            window.setFramerateLimit(60);
          }

        /**
         * @brief Set window background color from RGBA hex integer.
         *
         * Example: `0xE6E6E6FFu`
         */
    void setBackgroundColor(unsigned int hexCode) { backgroundColor = sf::Color(hexCode); }

        /**
         * @brief Add a widget by pointer.
         *
         * The widget must remain alive while the window is running.
         */
    void add(Widget* widget) { widgets.push_back(widget); }

        /**
         * @brief Add one or more widgets (pointer or reference forms).
         */
    template<typename... Ts>
    void add(Ts&&... widgets_list) {
        (add_widget(std::forward<Ts>(widgets_list)), ...);
    }

        /**
         * @brief Check if the native window is open.
         */
    bool isOpen() { return window.isOpen(); }

        /**
         * @brief Start event + render loop.
         *
         * Handles close/resize events, propagates all events to widgets,
         * clears background, renders widgets, and presents the frame.
         */
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

    /**
     * @brief Close the window.
     */
    void close() {
        window.close();
    }
};
