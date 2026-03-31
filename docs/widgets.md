# Widget Guide {#widgets_guide}

This page explains what each widget does, what properties matter, and how to use it quickly.

## Window

`Window` is the application host and render/event loop owner.

### Typical usage

@code{.cpp}
Window window(800, 600, "Velvet");
window.setBackgroundColor(0xE6E6E6FFu);
window.add(rootWidget);
window.run();
@endcode

---

## Stack / HStack / VStack

`Stack` is Velvet's layout primitive.

- `HStack`: places children left-to-right
- `VStack`: places children top-to-bottom

### Key APIs

- `setGap(float)` - space between children
- `setPadding(...)` - inner spacing
- `setWidth(float)`, `setHeight(float)`, `setSize(float, float)` - explicit layout size
- `setJustifyContent("start"|"center"|"end")` - main-axis placement
- `setAlignItems("start"|"center"|"end")` - cross-axis placement
- `setBackgroundColor(sf::Color)` - container background fill

### Example

@code{.cpp}
VStack panel(10);
panel.setPadding(16);
panel.setWidth(320);
panel.setJustifyContent("start");
panel.setAlignItems("center");
@endcode

**NOTE:** Stacks can be nested! You can do:

@code{.cpp}
HStack parent;
HStack one;
Vstack two;

one.add(two);

parent.add(one);
@endcode
---

## Label

`Label` displays styled text and supports a style map in the constructor.

### Constructor

@code{.cpp}
Label text("Hello", {
  {"fontSize", 24.f},
  {"fillColor", 0x222222FFu}
});
@endcode

### Supported style keys

- `fontPath` (`std::string`) e.g. `"src/assets/AdwaitaSans-Regular.ttf"`
- `fontSize` (`float`)
- `lineSpacing` (`float`)
- `letterSpacing` (`float`)
- `fillColor` (`unsigned int`, RGBA hex like `0xRRGGBBAA`)
- `outlineColor` (`unsigned int`)
- `outlineThickness` (`float`)
- `fontStyle` (`std::string`): `regular`, `bold`, `italic`, `underlined`, `strikethrough`
- `backgroundColor` (`unsigned int`)

### Runtime updates

- `setText(const std::string)`
- `overrideStyling(...)`

---

## Button

`Button` is clickable and fires `onclick` callback when left mouse is pressed while hovered.

### Constructor

@code{.cpp}
Button save(200, 44, "Save");
@endcode

### Event callback

@code{.cpp}
save.onclick = [&] {
  // your action
};
@endcode

---

## Slider

`Slider` is horizontal and emits continuous values in range `[from, to]`.

### Constructor

@code{.cpp}
Slider volume(240, 0.f, 100.f);
@endcode

### Event callback + value access

@code{.cpp}
volume.onchange = [&](float v) {
  // react to value changes while dragging
};

float current = volume.getValue();
@endcode

---

## Image

`Image` displays an image loaded from file.

### Constructor and scaling

@code{.cpp}
Image avatar("src/assets/avatar.png");
avatar.setScale(0.5f, 0.5f);
@endcode

---

## Composition example

@code{.cpp}
HStack root(24);

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
};

controls.add(heading, amount, apply);
preview.add(status, cat);
root.add(controls, preview);
@endcode
