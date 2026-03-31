#include <velvet/core>

int main() {
    Window window(700, 400, "Label Example");
    VStack root(18);
    root.setAlignItems("center");

    Label label1("This is also a label!");

    Label label2("This is a styled label!", {
        {"fontSize", 31.f},
        {"fontStyle", "italic"},
        {"fillColor", 0x428bacFFu}
    });

    Label label3("Something fancyy~", {
        {"fontSize", 40.f},
        {"fontStyle", "bold"},
        {"fillColor", 0xFFFFFFFFu},
        {"backgroundColor", 0x282c33FFu},
        {"letterSpacing", 3.f},
        {"outlineColor", 0xbe9760FFu},
        {"outlineThickness", 3.5f}
    });

    root.add(label1, label2, label3);
    window.add(root);

    window.run();
}
