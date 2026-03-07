#include <velvet/core>

int main() {
    Window window(800, 600, "Velvet");
    // HStack vstack(window, 10);

    // Button btn1(200, 120, "click me", sf::Color::White, 2);
    // Button btn2(200, 120, "poggies!", sf::Color::White, 2);

    // vstack.add(&btn1);
    // vstack.add(&btn2);


    Button btn(400, 400);
    window.add(&btn);
    btn.setPosition(200, 100);

    window.run();
}
