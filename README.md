<div align="center">

<h1>Velvet</h1>

<p>A high-level, beginner-friendly UI library for C++.</p>

[![License](https://img.shields.io/github/license/rushilkoul/velvet?style=flat-square)](LICENSE)
[![Language](https://img.shields.io/badge/language-C%2B%2B17-blue?style=flat-square)]()
[![Built with SFML](https://img.shields.io/badge/built%20with-SFML-8CC445?style=flat-square)](https://www.sfml-dev.org/)

</div>

---
Velvet is a beginner-friendly C++ UI library built on top of SFML. It is designed to be simple to use while providing possibilities for complex UI layouts.

<table>
  <tr>
    <th>Raw</th>
    <th>Styled</th>
  </tr>
  <tr>
    <td><img src="https://i.ibb.co/xtdjv4pV/image.png" width="360"/></td>
    <td><img src="https://i.ibb.co/zWRtXQcq/shot-2026-03-22-13-26-39.png" width="360"/></td>
  </tr>
</table>
With a bit more effort:
<img src="https://i.ibb.co/21jW7mC9/image.png" alt="Velvet Dashboard Demo" width="720"/>

---

## Contents

- [Features](#features)
- [Quick Start](#quick-start)
- [Installation](#installation)
- [Widgets](#widgets)
- [Docs](#docs)
- [Special Thanks](#special-thanks)

---

## Features
- **Widgets** - Pre-made widgets for a variety of use cases .
- **Stack layouts** - The core idea behind Velvet is centered around `Stack`s, which can be used to align widgets.
- **Customization** - Most widgets are easy to customize with various styling options.

---

## Quick Start

```cpp
#include <velvet/core>

int main() {
    Window window(800, 600, "My App");
    VStack root(10);

    Label heading("Hello, Velvet!", {{"fontSize", 48.f}});
    Button btn("Click me!");

    btn.onclick = [] {
        // handle click
    };

    root.add(heading, btn);
    window.add(root);
    window.run();
}
```

For a fuller example, a demo dashboard program can be seen in [`examples/DashboardEg.cpp`](examples/DashboardEg.cpp).

---

## Installation

### Prerequisites

Install CMake, Ninja, and SFML for your distro:

**Fedora / RHEL**
```bash
sudo dnf install cmake ninja sfml-devel
```

**Arch**
```bash
yay -S sfml2 cmake ninja
```

**Ubuntu / Debian**
```bash
sudo apt install cmake ninja-build libsfml-dev
```

### Build

```bash
git clone https://github.com/rushilkoul/velvet.git
cd velvet
make rebuild   # configure & build (run once for first-time setup)
make run       # compile & run src/main.cpp
```

> **VSCode users:** Install the [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) extension for accurate C++ IntelliSense.

---

## Widgets

A list and usage guide for all widgets can be found in the documentation's [widget guide page](https://rushilkoul.github.io/velvet/widgets_guide.html).

### Styling

Some of the widgets accept an optional style map at construction. For example:

```cpp
Label title("Dashboard", {
    {"fontSize",  28.f},
    {"fillColor", 0x1F1F1FFFu},
    {"fontStyle", "bold"},
});

Button submit("Submit", {
    {"backgroundColor",      0x6C63FFFFu},
    {"hoverBackgroundColor", 0x574FD6FFu},
    {"fontColor",            0xFFFFFFFFu},
    {"width",                200.f},
    {"height",               48.f},
});
```

Colors are `unsigned int` RGBA hex values (`0xRRGGBBAAu`).

### Layout

`VStack` and `HStack` support flex-style layout options:

```cpp
VStack sidebar(15);
sidebar.setWidth(300);
sidebar.setHeight(600);
sidebar.setPadding(16);
sidebar.setJustifyContent("center");   // "start" | "center" | "end"
sidebar.setAlignItems("start");        // "start" | "center" | "end"
sidebar.setBackgroundColor(sf::Color(30, 30, 30, 200));
```

---

## Documentation
The hosted documentation for Velvet can be found at: https://rushilkoul.github.io/velvet/. 

### Building the docs

Install Doxygen:

```bash
# Fedora / RHEL
sudo dnf install doxygen
```

Generate documentation: 
```bash
make docs
```
Docs are written to `build/docs/html/index.html`/

---

## Special Thanks
 - Thanks to [SFML](https://www.sfml-dev.org/)'s developers and maintainers for their amazing library.
 
 - Velvet doxygen docs use very clean CSS from [doxygen-awesome-css](https://github.com/jothepro/doxygen-awesome-css). Big ups to them!

- [Adwaita](https://gitlab.gnome.org/GNOME/adwaita-fonts) is the default font used in Velvet, beautifully created by the folks at [The Gnome Foundation](https://foundation.gnome.org/).
