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

    InputField entry1;
    InputField entry2("type something...", {
        {"fontSize", 55.f},
        {"backgroundColor", 0x97bac4ffu},
        {"width", 260.f}
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
        {"fontStyle", "bold"},
        {"fontPath", "src/assets/space-grotesk.ttf"}
    });

    Label bleh("Counter: 0");
    
    HStack message(0);
    message.setPadding(0, 0, 0 , 20);

    Label lol1("this cat is ",{{"fontStyle", "italic"}});
    Label lol2("very precious",{
        {"fontStyle", "italic"},
        {"backgroundColor", 0xFFED29FFu}
    });
    Label lol3(". take good care of it, traveller.",{{"fontStyle", "italic"}});

    message.add(lol1, lol2, lol3);

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
    };
    
    slider.onchange = [&](float v) {
        valueLabel.setText("Slider Value: " + std::to_string((int)v));
        img.setScale(0.3 + v/200.0f, 0.3 + v/200.0f);
    };

    controls.setBackgroundColor(sf::Color(211, 163, 255, 220));controls.setHeight(570);
    controls.add(
        title,
        valueLabel,
        entry1,
        entry2,
        slider,
        incrementBtn,
        resetBtn
    );

    preview.add(
        previewTitle,
        dynamicText,
        bleh,
        message,
        img
    );

    root.add(controls,&preview);

    window.add(root);
    window.run();
}
