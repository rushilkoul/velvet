#include <velvet/core>

int main() {
    Window window(700, 400, "Button Example");
    VStack root(18);

    int count = 0;

    Label counter("Count: 0", {
        {"fontSize", 30.f},
    });

    Button btn(200, 50, "Click me!");
    btn.onclick = [&] {
        count++;
        counter.setText("Count: " + std::to_string(count));
    };

    Button reset(200, 50, "Reset", {
        {"backgroundColor", 0xFF736dFFu},
        {"outlineColor", 0xd3b020FFu},
        {"outlineThickness", 4.f},
        {"hoverBackgroundColor", 0xd3b020FFu}
    });
    reset.onclick = [&] {
        count = 0;
        counter.setText("Count: 0");
    };

    root.add(counter, btn, reset);
    window.add(root);

    window.run();
}
