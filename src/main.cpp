#include <velvet/core>

int main() {
    Window window(1000, 700, "Welcome to Velvet");
    VStack root(20);

    Stack stack(StackDirection::Horizontal, 10);

    root.setAlignItems("center");
    root.setWidth(1000);
    root.setPadding(0, 0, 50, 0);

    Label title("Welcome to Velvet!", {
        {"fontSize", 48.f },
    });


    Label sub1("A ");
    Label sub2("beginner-first",{
        {"fontStyle", "italic"},
        {"backgroundColor", 0xFFED29FFu}
    });
    Label sub3(" C++ GUI framework");

    HStack subtitle;
    subtitle.setPadding(0);
    subtitle.setWidth(340);
    subtitle.add(sub1, sub2, sub3);


    Label pad("");
    Label p("Get started by reading the documentation. Feel free to explore the codebase!");

    Button b(":)", {
        {"hoverFontColor", 0xFFFFFFFFu},
        {"hoverBackgroundColor", 0x444444FFu},
    });

    Image img("src/assets/funnycat.png");
    b.onclick = [&]() {
        // open browser annd launch docs!?!?
        img.setImage("src/assets/evilcat.png");
    };


    root.add(title, subtitle, pad, p, b, img);
    window.add(root);

    window.run();
}
