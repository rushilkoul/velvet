# Velvet

A beginner-friendly GUI framework built on SFML for creating beautiful desktop applications in C++.

Instead of dealing with low-level frameworks directly, Velvet provides high-level components like buttons, sliders, and layout systems _that just work_. It handles rendering, layout, and interaction internally so you can focus on building your app.

## Quick example usage

```cpp

#include <velvet/core>

int main() {
    Window window(800, 600, "My App");
    VStack root(10);
    
    Label l1("Hello, Velvet!", { {"fontSize", 48.f} });
    Button btn(200, 50, "click me!");

    root.add(l1, btn);
    window.add(root);
    
    window.run();

    return 0;
}
```

| raw | styled |
| :--- | :--- |
<img src="https://i.ibb.co/xtdjv4pV/image.png" alt="image" border="0"> | <img align="center" src="https://i.ibb.co/zWRtXQcq/shot-2026-03-22-13-26-39.png" alt="velvet_output_img"> 

a bit more effort:

<img src="https://i.ibb.co/21jW7mC9/image.png" alt="image" border="0">

## Get started

### Prerequisites

**Fedora/RH:**
```bash
sudo dnf install cmake ninja sfml-devel
```

**Arch:**
```bash
yay -S sfml2 cmake ninja
```

**Ubuntu/Debian:**
```bash
sudo apt install cmake ninja-build libsfml-dev
```


### Project Setup
```bash
# clone
git clone https://github.com/rushilkoul/velvet.git
cd velvet
```
```bash
make run   # runs src/main.cpp
```
**VSCode Users:** Install the [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) extension for proper (better) C++ support.


### Building docs

install Doxygen:

```bash
# Fedora/RH
sudo dnf install doxygen

# Arch
yay -S doxygen

# Ubuntu/Debian
sudo apt install doxygen
```

then:

```bash
make docs
```

Docs are written to `build/docs/html/index.html`.

Useful generated pages:

- `index.html` (overview + quickstart links)
- `quickstart.html`
- `widgets_guide.html` (widget-by-widget usage)
- `screenshot_guide.html` (how to embed widget screenshots)

Velvet docs use very clean CSS from [doxygen-awesome-css](https://github.com/jothepro/doxygen-awesome-css). Big ups to them!
