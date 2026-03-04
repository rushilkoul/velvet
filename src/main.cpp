#include <velvet/widgets/Button.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Velvet");

    std::vector<Button> widgets = {
        Button(300, 250, 200, 100, "xd", sf::Color::Cyan, 10),
        Button(20, 20, 250, 125, "potat", sf::Color::Cyan, 1)
    };


    while (window.isOpen())
    {   
        sf::Event event;
        sf::Cursor cursor;

        while (window.pollEvent(event)) {
            if (cursor.loadFromSystem(sf::Cursor::Arrow)) window.setMouseCursor(cursor);

            for (Button& widget : widgets) {
                widget.handleEvent(event);
            }

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear(sf::Color(7, 7, 9));

        // IDK WHY THE TEXT DOESNT RENDER
        // RUSHIL PLEASE FIX THIS SHIT MERE SE NAW HORA
        // FIGURE IT OUT YOU CAN DO IT
        // GAMBARE GAMBARE SENPAI
        for (Button& widget : widgets) {
            widget.render(window);
        }

        window.display();
    }
}
