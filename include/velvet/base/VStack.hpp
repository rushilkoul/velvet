#pragma once
#include <velvet/base/Widget.hpp>
#include <velvet/base/Window.hpp>

class VStack {
    Window& window;
    float gap;
    float xPos, yPos;
public:
    inline static int vOffset = 0;
    VStack(Window& _window, float gap=0)
        : window(_window), gap(gap)  
        {}


    void add(Widget* widget) {
        widget->setPosition(0, vOffset);
        window.add(widget);
        vOffset += widget->getBounds().y;
        vOffset += gap;
    }
};
