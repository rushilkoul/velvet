#pragma once
#include <velvet/base/Widget.hpp>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

enum class StackDirection { Horizontal, Vertical };
enum class StackJustify { Start, Center, End };
enum class StackAlign { Start, Center, End };

class Stack : public Widget {
private:
    float xPos = 0;
    float yPos = 0;

    float cachedWidth = 0;
    float cachedHeight = 0;
    float explicitWidth = 0;
    float explicitHeight = 0;

    std::vector<Widget*> children;

    StackDirection direction;
    StackJustify justify = StackJustify::Start;
    StackAlign align = StackAlign::Start;

    float gap;
    float padding = 8.0f;

    sf::Color backgroundColor = sf::Color(0, 0, 0, 0);
    sf::RectangleShape backgroundShape;

    bool dirty = false;

    static std::string normalize(std::string value) {
        std::transform(value.begin(), value.end(), value.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return value;
    }

    static StackJustify parseJustifyOrFallback(const std::string& value) {
        const std::string normalized = normalize(value);

        if (normalized == "center") return StackJustify::Center;
        if (normalized == "start") return StackJustify::Start;
        if (normalized == "end") return StackJustify::End;

        std::cerr << "[Velvet][Stack] Unsupported justify value: '" << value
                  << "'. Falling back to 'start'.\n";
        return StackJustify::Start;
    }

    static StackAlign parseAlignOrFallback(const std::string& value) {
        const std::string normalized = normalize(value);

        if (normalized == "center") return StackAlign::Center;
        if (normalized == "start") return StackAlign::Start;
        if (normalized == "end") return StackAlign::End;

        std::cerr << "\033[33mWarning: Invalid style property: '" << value << "'\033[0m" << std::endl;
        return StackAlign::Start;
    }

    void draw(sf::RenderWindow& window) override {
        if (backgroundColor.a > 0) {
            window.draw(backgroundShape);
        }
        for (Widget* child : children) {
            child->render(window);
        }
    }

    void update(sf::RenderWindow& window) override {
        if (dirty) {
            recalculateChildPositions();
            dirty = false;
        }

    }

    float getContentMainSize() {
        if (children.empty()) return 0;

        float total = 0;
        for (Widget* child : children) {
            const sf::Vector2f dims = child->getDimensions();
            total += (direction == StackDirection::Horizontal) ? dims.x : dims.y;
        }

        total += gap * static_cast<float>(children.size() - 1);
        return total;
    }

    void recalculateCachedDimensions() {
        cachedWidth = 0;
        cachedHeight = 0;

        for (Widget* child : children) {
            const sf::Vector2f dims = child->getDimensions();
            if (direction == StackDirection::Horizontal) {
                cachedWidth += dims.x;
                cachedHeight = std::max(cachedHeight, dims.y);
            } else {
                cachedHeight += dims.y;
                cachedWidth = std::max(cachedWidth, dims.x);
            }
        }

        if (!children.empty()) {
            if (direction == StackDirection::Horizontal)
                cachedWidth += gap * static_cast<float>(children.size() - 1);
            else
                cachedHeight += gap * static_cast<float>(children.size() - 1);
        }
    }

    float calculateStartOffset(float available, float content) const {
        if (available <= content) return 0;

        const float remaining = available - content;
        if (justify == StackJustify::Center) return remaining * 0.5f;
        if (justify == StackJustify::End) return remaining;

        return 0;
    }

    float calculateCrossOffset(float available, float content) const {
        if (available <= content) return 0;

        const float remaining = available - content;
        if (align == StackAlign::Center) return remaining * 0.5f;
        if (align == StackAlign::End) return remaining;

        return 0;
    }

    void recalculateChildPositions() {
        recalculateCachedDimensions();

        const float contentMain = getContentMainSize();
        const float availableMain =
            (direction == StackDirection::Horizontal) ? explicitWidth : explicitHeight;
        const float startMain = calculateStartOffset(availableMain, contentMain);

        float pos = (direction == StackDirection::Horizontal) ? xPos + padding + startMain : yPos + padding + startMain;

        for (Widget* child : children) {
            const sf::Vector2f dims = child->getDimensions();

            if (direction == StackDirection::Horizontal) {
                const float crossOffset = calculateCrossOffset(explicitHeight, dims.y);
                child->setPosition(pos, yPos + padding + crossOffset);
                pos += dims.x + gap;
            } else {
                const float crossOffset = calculateCrossOffset(explicitWidth, dims.x);
                child->setPosition(xPos + padding + crossOffset, pos);
                pos += dims.y + gap;
            }
        }

        const float totalWidth = std::max(cachedWidth, explicitWidth) + padding * 2;
        const float totalHeight = std::max(cachedHeight, explicitHeight) + padding * 2;
        backgroundShape.setPosition(xPos, yPos);
        backgroundShape.setSize(sf::Vector2f(totalWidth, totalHeight));
        backgroundShape.setFillColor(backgroundColor);
    }

public:
    Stack(StackDirection dir, float gap = 0) : direction(dir), gap(gap) {}
    void render(sf::RenderWindow& window) override {
        update(window);
        draw(window);
    }

    void add(Widget* widget) {
        children.push_back(widget);
        dirty = true;
    }

    template<typename... Ts>
    void add(Ts&&... widgets) {
        (add_widget(std::forward<Ts>(widgets)), ...);
    }

private:
    void add_widget(Widget* w) { add(w); }
    void add_widget(Widget& w) { add(&w); }

public:
    void setPosition(float x, float y) override {
        if (xPos != x || yPos != y) {
            xPos = x;
            yPos = y;
            dirty = true;
        }
    }

    sf::Vector2f getDimensions() override {
        return sf::Vector2f(
            std::max(cachedWidth, explicitWidth) + padding * 2,
            std::max(cachedHeight, explicitHeight) + padding * 2
        );
    }

    void handleEvent(const sf::Event& event, sf::RenderWindow &window) override {
        for (Widget* child : children) {
            child->handleEvent(event, window);
        }
    }

    void setGap(float g) {
        if (gap != g) {
            gap = g;
            dirty = true;
        }
    }

    float getGap() const { return gap; }

    void setJustifyContent(StackJustify value) {
        if (justify != value) {
            justify = value;
            dirty = true;
        }
    }

    void setJustifyContent(const std::string& value) {
        setJustifyContent(parseJustifyOrFallback(value));
    }

    void setAlignItems(StackAlign value) {
        if (align != value) {
            align = value;
            dirty = true;
        }
    }

    void setAlignItems(const std::string& value) {
        setAlignItems(parseAlignOrFallback(value));
    }

    void setSize(float width, float height) {
        if (explicitWidth != width || explicitHeight != height) {
            explicitWidth = width;
            explicitHeight = height;
            dirty = true;
        }
    }

    void setWidth(float width) {
        if (explicitWidth != width) {
            explicitWidth = width;
            dirty = true;
        }
    }

    void setHeight(float height) {
        if (explicitHeight != height) {
            explicitHeight = height;
            dirty = true;
        }
    }

    void setPadding(float p) {
        if (padding != p) {
            padding = p;
            dirty = true;
        }
    }

    float getPadding() const { return padding; }

    void setBackgroundColor(sf::Color color) {
        if (backgroundColor.r != color.r || backgroundColor.g != color.g ||
            backgroundColor.b != color.b || backgroundColor.a != color.a) {
            backgroundColor = color;
            backgroundShape.setFillColor(backgroundColor);
            dirty = true;
        }
    }
};

// preserve HStack and VStack class names for backwards compatibility
// (to be fair its like 4 commits ago but still cmon)

class HStack : public Stack {
public:
    HStack(float gap = 0) : Stack(StackDirection::Horizontal, gap) {}
};

class VStack : public Stack {
public:
    VStack(float gap = 0) : Stack(StackDirection::Vertical, gap) {}
};
