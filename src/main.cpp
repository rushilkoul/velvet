#include "velvet/widgets/Stack.hpp"
#include <velvet/core>
#include <iostream>

void extremelysad(const std::string s) {
    std::cout << "bottom of the morning " + s + "\n"; 
}

int main() {
    Window window(800, 900, "Velvet");

    VStack root(10);
    
    Button btn(100, 50,"hello");
    Button btn2(100, 50,"hello 2");

    Slider s1(200, 0, 100);
    Slider s2(300, 42, 67);

    Label l1("hello", 25);
    Label l2("hello", 50);
    Label l3("hello", 100);

    Image img("src/assets/funnycat.png");
    img.setScale(0.5, 0.5);


    root.add(btn, s1, l2, btn2, s2, l1, img, l3);

    btn.onclick = [] { std::cout << "top of the morning :D\n"; };
    int i = 0;
    btn2.onclick = [&] { 
        extremelysad("T_T");
        l2.setText("good morning america " + std::to_string(i));
        i++;
    };

    window.add(root);
    window.run();
}