#include <velvet/widgets/Button.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Velvet");

    Button btn(300, 250, 200, 100, "xd");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear(sf::Color(7, 7, 9));
        btn.render(window);
        window.display();
    }
}
