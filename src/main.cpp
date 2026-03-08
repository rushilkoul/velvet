#include <velvet/core>

/*
int main() {
    Window window(800, 600, "Velvet");
    //VStack vstack(window, 10);
    VStack vstack(10);

    Button btn1(200, 120, "click me", sf::Color::White, 2);
    Button btn2(200, 120, "poggies!", sf::Color::White, 2);
    Button btn3(200, 120, "poggies!", sf::Color::White, 2);

    vstack.add(&btn1);
    vstack.add(&btn2);

    window.add(&vstack);

    window.run();
}
*/

///*
int main() {
    Window window(800, 600, "Velvet");

    VStack mainStack(10);

    HStack s1(10);

    HStack s2(10);

    HStack s3(10);
    VStack s3a(10);
    VStack s3b(10);

    Button b1(100, 100, "EGG");
    Button b2(100, 100, "EGG");
    Button b3(100, 100, "EGG");

    Button b4(100, 300, "EGG");
    Button b5(100, 300, "EGG");
    Button b6(100, 300, "EGG");

    Button b7(150, 100, "EGG");
    Button b8(150, 100, "EGG");

    Button b9(150, 100, "EGG");
    Button b10(150, 100, "EGG");

    s1.add(&b1);
    s1.add(&b2);
    s1.add(&b3);

    s2.add(&b4);
    s2.add(&b5);
    s2.add(&b6);

    s3a.add(&b7);
    s3a.add(&b8);
    
    s3b.add(&b9);
    s3b.add(&b10);

    mainStack.add(&s1);
    mainStack.add(&s2);
    mainStack.add(&s3);

    s3.add(&s3a);
    s3.add(&s3b);
    
    window.add(&mainStack);

    window.run();
}
//*/