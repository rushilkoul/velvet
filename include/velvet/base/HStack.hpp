#pragma once
#include <velvet/base/Widget.hpp>
#include <velvet/base/Window.hpp>

class HStack {
    Window& window;
    float gap;
public:
    inline static int hOffset = 0;
    HStack(Window& _window, float gap=0)
        : window(_window), gap(gap)  
        {}


    void add(Widget* widget) {
        widget->setPosition(hOffset, 0);
        window.add(widget);
        hOffset += widget->getBounds().x;
        hOffset += gap;
    }
};
