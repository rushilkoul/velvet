# Widget Guide {#widgets_guide}

This page explains what each widget does, what properties matter, and how to use them quickly.

## Window

`Window` is the application host and render/event loop owner.

### Constructor:
@code{.cpp}
Window (float width, float height, std::string title);
@endcode

### Key Functions:

- `setBackgroundColor(unsigned int color)` - set background color of the window. Use an RGBA hex like `0xRRGGBBAA`
- `add(Widgets)` - add Widgets/Layouts to the window
- `bool isOpen()` - returns if window is open
- `close()` - closes the window

### Typical usage

@code{.cpp}
Window window(800, 600, "Velvet");
window.setBackgroundColor(0xE6E6E6FFu);
window.add(Widget);

window.run();
@endcode

---

## Stack / HStack / VStack

`Stack` is Velvet's layout primitive.

- `HStack`: places children left-to-right
- `VStack`: places children top-to-bottom

> Note from the developer:\n
> Stack is similar to a CSS flexbox. One can relate a HStack to a CSS div `display: flex` with `flex-direction: row`, and VStack to `flex-direction: column`. Similarly, `padding` and `gap`, `justify-content` and `align-items` all work the similarly in Velvet.

### Key APIs
- `setWidth(float)`, `setHeight(float)`, `setSize(float, float)` - set explicit layout size
- `setJustifyContent("start"|"center"|"end")` - main-axis placement
- `setAlignItems("start"|"center"|"end")` - cross-axis placement
- `setBackgroundColor(sf::Color)` - container background fill
- `setGap(float)` - set spacing between children

**Setting padding:**
- `setPadding(float all)` - all sides
- `setPadding(float x, float y)` - horizontal and vertical
- `setPadding(float left, right, top, bottom)` - individual directions

Default padding: `8px`, can be configured with the above functions

### Constructor: 
`gap`: spacing between children (in px)
@code{.cpp}
Stack stack(StackDirection::Horizontal, float gap);   // horizontal stack
Stack stack(StackDirection::Vertical, float gap);     // vertical stack

@endcode
Or the more convenient `HStack` and `VStack`:

@code{.cpp}
HStack stack(float gap);    // horizontal stack
VStack stack(float gap);    // vertical stack
VStack stack;               // default gap: 0px
@endcode



### Example

@code{.cpp}
VStack panel(10); // gap

panel.setPadding(16);
panel.setWidth(320);
panel.setJustifyContent("start");
panel.setAlignItems("center");
@endcode

**NOTE:** Stacks can be nested! You can do:

@code{.cpp}
HStack parent, one, two;
Vstack three;

three.add(one, two);
parent.add(three);
@endcode
---

## Label

`Label` displays styled text. Supports a style map in the constructor.

### Constructor

@code{.cpp}

Label text("Hello, world!");    // default styling parameters
// or:
Label text("Hello, world!", {
  {"fontSize", 24.f},
  {"fillColor", 0x222222FFu},
  ...
});
@endcode

### Supported style keys

- `fontPath` (`std::string`) default: `"src/assets/AdwaitaSans-Regular.ttf"`
- `fontSize` (`float`)
- `lineSpacing` (`float`)
- `letterSpacing` (`float`)
- `fillColor` (`unsigned int`, RGBA hex like `0xRRGGBBAA`)
- `outlineColor` (`unsigned int`)
- `outlineThickness` (`float`)
- `fontStyle` (`std::string`): `regular`, `bold`, `italic`, `underlined`, `strikethrough`
- `backgroundColor` (`unsigned int`)

### Runtime updates

- `setText(const std::string)` - change the label text on runtime
- `overrideStyling({...})` - Update styling keys on runtime

---

## Button

`Button` implements, well, a button.

### Constructor

@code{.cpp}
Button save(float width, float height, std::string buttonText);
@endcode

### Event callback

Fires `onclick` callback when left mouse is pressed while hovered.
@code{.cpp}
btn.onclick = [&] {
  // your action
};
@endcode

---

## Slider

`Slider` is horizontal and emits continuous values in range `[from, to]`.

### Constructor

@code{.cpp}
Slider slider(float width, float from, float to);
@endcode

### Event callback + value access

@code{.cpp}
Slider volume(240, 0.f, 100.f);
volume.onchange = [&](float v) {
  // react to value changes while dragging
};

@endcode
Get current value of slider: 
@code{.cpp}
float current = volume.getValue();
@endcode

---

## InputField

`InputField` is a single-line text box that accepts keyboard input, and shows a placeholder when empty.

### Constructor

@code{.cpp}
InputField field("Placeholder here!");

InputField nameField("Enter your name", {
  {"width", 260.f},
  {"fontSize", 18.f},
  {"backgroundColor", 0xFFFFFFFFu},
  ...
});
@endcode

### Supported style keys

- `fontPath` (`std::string`) e.g. "src/assets/AdwaitaSans-Regular.ttf"
- `fontSize` (`float`)
- `letterSpacing` (`float`)
- `fontColor` (`unsigned int`) text color, RGBA hex like `0xRRGGBBAA`
- `outlineColor` (`unsigned int`) inactive border color
- `activeOutlineColor` (`unsigned int`) intended active border color when focused
- `backgroundColor` (`unsigned int`) input background fill
- `placeholderColor` (`unsigned int`) color of the placeholder text
- `width` (`float`) width of the input box

### Runtime usage
- `overrideStyling({...})` - Update styling keys on runtime

**Public variables:**
- `content` - (`std::string`) Read or modify the current content
- `placeholder` - (`std::string`) Modify to update placeholder text 

---

## Image

`Image` displays an image loaded from file.

### Constructor

@code{.cpp}
Image img(std::string filePath);
@endcode

### Example usage:
@code{.cpp}
Image avatar("src/assets/evilcat.png");
avatar.setScale(0.5f, 0.5f);
@endcode

### Functions

- `setImage(std::string filePath)`- Set the image path on runtime.
- `setScale(float x, float y)`- Set the image scale relative to the image's actual dimensions.

---

## Composition example

@code{.cpp}
#include <velvet/core>

int main() {
    Window window(600, 400, "test");

    HStack root(200);
    
    VStack controls(12);
    
    Label heading("Controls", {{"fontSize", 24.f}});
    Slider amount(200, 0.f, 100.f);
    Button apply(200, 40, "Apply");
    
    VStack preview(12);
    
    Label status("Ready");
    Image cat("src/assets/funnycat.png");
    cat.setScale(0.35f, 0.35f);
    
    apply.onclick = [&] {
      status.setText("Applied: " + std::to_string((int)amount.getValue()));
      cat.setImage("src/assets/evilcat.png");
    };
    
    controls.add(heading, amount, apply);
    preview.add(status, cat);
    root.add(controls, preview);
    
    window.add(root);
    window.run();
}

@endcode
