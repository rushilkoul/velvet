#include <velvet/core>

int main() {
    Window window(1000, 900, "Welcome to Velvet");
    VStack root(20);

    Stack stack(StackDirection::Horizontal, 10);

    root.setAlignItems("center");
    root.setWidth(1000);
    root.setPadding(0, 0, 50, 0);

    Image logo("src/assets/VelvetLogo.png");
    logo.setScale(0.25, 0.25);

    Label title("Welcome to Velvet!", {
        {"fontSize", 48.f },
        {"fontStyle", "bold"}
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

    Button b(100, 50, "Explore");


    root.add(logo, title, subtitle, pad, p, b);
    window.add(root);

    window.run();
}
