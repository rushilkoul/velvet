#include <velvet/core>
#include <iostream>

void extremelysad(const std::string s) {
    std::cout << "bottom of the morning " + s + "\n"; 
}

int main() {
    Window window(800, 600, "Velvet");

    VStack root(10);
    
    Button btn(100, 50,"hello");
    Button btn2(100, 50,"hello 2");
    Slider s1(200, 0, 100);
    Slider s2(300, 42, 67);

    root.add(&btn);
    root.add(&s1);
    root.add(&btn2);
    root.add(&s2);

    btn.onclick = [] { std::cout << "top of the morning :D\n"; };

    btn2.onclick = [] { 
        extremelysad("T_T");
    };

    window.add(&root);
    window.run();
}