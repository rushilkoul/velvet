#include <velvet/core>

int main() {
    Window window(800, 600, "Velvet");

    Button btn1(300, 250, 200, 100, "click me", sf::Color::White, 2);
    Button btn2(20, 20, 250, 125, "poggies!", sf::Color::White, 2);

    window.add(&btn1);
    window.add(&btn2);

    window.run();
}
