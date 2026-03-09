#pragma once
#include <velvet/base/Widget.hpp>
#include <vector>

enum class StackDirection { Horizontal, Vertical };

class Stack : public Widget {
private:
    float xPos = 0;
    float yPos = 0;

    float nextPos = 0;
    float cachedWidth = 0;
    float cachedHeight = 0;

    std::vector<Widget*> children;

    StackDirection direction;

    float gap;

    bool dirty = false;

    void draw(sf::RenderWindow& window) override {
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

    void recalculateChildPositions() {
        float pos = (direction == StackDirection::Horizontal) ? xPos : yPos;

        for (Widget* child : children) {
            if (direction == StackDirection::Horizontal) {
                child->setPosition(pos, yPos);
                pos += child->getDimensions().x + gap;
            } else {
                child->setPosition(xPos, pos);
                pos += child->getDimensions().y + gap;
            }
        }
        nextPos = pos;
    }

public:
    Stack(StackDirection dir, float gap = 0) : direction(dir), gap(gap), nextPos(0) {}

    void render(sf::RenderWindow& window) override {
        update(window);
        draw(window);
    }

    void add(Widget* widget) {

        sf::Vector2f dims = widget->getDimensions();

        if (direction == StackDirection::Horizontal) {
            widget->setPosition(xPos + nextPos, yPos);

            nextPos += dims.x + gap;
            cachedWidth = nextPos - gap;

            if (dims.y > cachedHeight) cachedHeight = dims.y;
        } else {
            widget->setPosition(xPos, yPos + nextPos);

            nextPos += dims.y + gap;
            cachedHeight = nextPos - gap;

            if (dims.x > cachedWidth) cachedWidth = dims.x;
        }

        children.push_back(widget);
    }

    void setPosition(float x, float y) override {
        if (xPos != x || yPos != y) {
            xPos = x;
            yPos = y;
            dirty = true;
        }
    }

    sf::Vector2f getDimensions() override {
        return sf::Vector2f(cachedWidth, cachedHeight);
    }

    void handleEvent(const sf::Event& event) override {
        for (Widget* child : children) {
            child->handleEvent(event);
        }
    }

    void setGap(float g) {
        if (gap != g) {
            gap = g;
            nextPos = 0;
            cachedWidth = 0;
            cachedHeight = 0;

            for (Widget* child : children) {
                sf::Vector2f dims = child->getDimensions();

                if (direction == StackDirection::Horizontal) {
                    nextPos += dims.x + gap;
                    if (dims.y > cachedHeight) cachedHeight = dims.y;

                } else {
                    nextPos += dims.y + gap;
                    if (dims.x > cachedWidth) cachedWidth = dims.x;

                }

            }
            if (!children.empty()) {
                if (direction == StackDirection::Horizontal)
                    cachedWidth = nextPos - gap;
                else
                    cachedHeight = nextPos - gap;
            }
            dirty = true;
        }
    }

    float getGap() const { return gap; }
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
