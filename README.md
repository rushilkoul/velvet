# Velvet

A beginner-friendly GUI framework built on SFML for creating beautiful desktop applications in C++.

Instead of dealing with low-level frameworks directly, Velvet provides high-level components like buttons, sliders, and layout systems _that just work_. It handles rendering, layout, and interaction internally so you can focus on building your app.

## Quick example usage
```cpp

#include <velvet/core>

int main() {
    Window window(800, 600, "My App");
    VStack root(10);
    
    Label l1("Hello, Velvet!", 48);
    Button btn(100, 50, "click me!");
    
    btn.onclick = [] {
        std::cout << "button was clicked \n";
    };

    root.add(l1, btn);
    window.add(root);
    
    window.run();

    return 0;
}
```

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
