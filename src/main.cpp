#include <velvet/core>

///*
int main() {
    Window window(800, 600, "Velvet");

    VStack root(10);
    
    Button btn(100, 50,"hello");
    Button btn2(100, 50,"hello 2");
    Slider s1(200, 0, 100);
    Slider s2(300, 0, 100);

    root.add(&btn);
    root.add(&s1);
    root.add(&btn2);
    root.add(&s2);

    window.add(&root);
    window.run();
}
//*/

/*
int main() {
    Window window(800, 600, "Velvet");

    Slider s(200, 0, 100);
    window.add(&s);

    //window.add(&root);
    window.run();
}
*/