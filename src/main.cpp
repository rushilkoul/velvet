#include <velvet/core>
#include <string>

int main() {
    Window window(1000, 600, "Velvet");

    HStack root(30);
    root.setAlignItems("start");

    // left panel //////////////////////////////////
    VStack controls(15);
    controls.setWidth(300);
    controls.setJustifyContent("center");

    Label title("Velvet Demo", {
        {"fontSize", 28.f}, 
        {"fillColor", 0x1F1F1FFFu}
    });
    
    Label valueLabel("Slider Value: ", {{"fontSize", 18.f}});

    Slider slider(200, 0, 100);

    Button incrementBtn(200, 40, "Increment counter");
    Button resetBtn(200, 40, "Reset");

    // right panel //////////////////////////////////
    VStack preview(20);
    preview.setAlignItems("center");
    
    Label previewTitle("Live Preview", {
        {"fontSize", 18.f},
    });
    
    Label dynamicText("Hello, Velvet!", {
        {"fontSize", 40.f}, 
        {"fillColor", 0xA447FAFFu},
        {"fontStyle", "bold"}

    });

    Label bleh("Counter: 0");
    Label lol("this cat is very precious. take care of it, traveller.",
    {
        {"fontStyle", "italic"}
    });

    Image img("src/assets/funnycat.png");
    img.setScale(0.4, 0.4);


    /////////////////////
    int counter = 0;

    incrementBtn.onclick = [&] {
        counter++;
            bleh.setText("Count: " + std::to_string(counter));
    };
    
    resetBtn.onclick = [&] {
        counter = 0;
            bleh.setText("Count: " + std::to_string(counter));
        // dynamicText.setText("Reset!");
    };
    
    slider.onchange = [&](float v) {
        valueLabel.setText("Slider Value: " + std::to_string((int)v));
        img.setScale(0.3 + v/200.0f, 0.3 + v/200.0f);
    };

    controls.setBackgroundColor(sf::Color(211, 163, 255, 220));controls.setHeight(570);
    // controls.setBackgroundColor(sf::Color(211, 163, 255, 220));controls.setHeight(570);
    controls.add(
        title,
        valueLabel,
        slider,
        incrementBtn,
        resetBtn
    );

    preview.add(
        previewTitle,
        dynamicText,
        bleh,
        lol,
        img
    );

    root.add(controls,&preview);

    window.add(root);
    window.run();
}