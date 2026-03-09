#include <velvet/core>

int main() {
    Window window(800, 600, "Velvet");

    VStack root(10);
    
    Button btn(100, 50,"hello");
    Button btn2(100, 50,"hello 2");

    root.add(&btn);
    root.add(&btn2);

    window.add(&root);
    window.run();
}