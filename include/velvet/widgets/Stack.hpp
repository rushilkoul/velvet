#pragma once
#include <velvet/base/Widget.hpp>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

/** @brief Layout direction for @ref Stack. */
enum class StackDirection { Horizontal, Vertical };
/** @brief Main-axis content alignment for @ref Stack. */
enum class StackJustify { Start, Center, End };
/** @brief Cross-axis item alignment for @ref Stack. */
enum class StackAlign { Start, Center, End };

/**
 * @brief Container widget that arranges children in a row or column.
 *
 * `Stack` is Velvet's primary layout primitive.
 *
 * - Horizontal mode (`HStack`): children left-to-right
 * - Vertical mode (`VStack`): children top-to-bottom
 *
 * It supports gap, padding, explicit size, justify/align options,
 * and optional background color.
 */
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
    float paddingLeft = 8.0f;
    float paddingRight = 8.0f;
    float paddingTop = 8.0f;
    float paddingBottom = 8.0f;

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

        float pos = (direction == StackDirection::Horizontal)
                ? xPos + paddingLeft + startMain
                : yPos + paddingTop + startMain;

        for (Widget* child : children) {
            const sf::Vector2f dims = child->getDimensions();

            if (direction == StackDirection::Horizontal) {
                const float crossOffset = calculateCrossOffset(explicitHeight, dims.y);
                child->setPosition(pos, yPos + paddingTop + crossOffset);
                pos += dims.x + gap;
            } else {
                const float crossOffset = calculateCrossOffset(explicitWidth, dims.x);
                child->setPosition(xPos + paddingLeft + crossOffset, pos);
                pos += dims.y + gap;
            }
        }

        const float totalWidth = std::max(cachedWidth, explicitWidth) + paddingLeft + paddingRight;
        const float totalHeight = std::max(cachedHeight, explicitHeight) + paddingTop + paddingBottom;
        backgroundShape.setPosition(xPos, yPos);
        backgroundShape.setSize(sf::Vector2f(totalWidth, totalHeight));
        backgroundShape.setFillColor(backgroundColor);
    }

public:
    /**
     * @brief Construct a stack with direction and optional gap.
     */
    Stack(StackDirection dir, float gap = 0) : direction(dir), gap(gap) {}

    /**
     * @brief Render stack background and child widgets.
     */
    void render(sf::RenderWindow& window) override {
        update(window);
        draw(window);
    }

    /**
     * @brief Add a child widget pointer.
     *
     * Child widgets must outlive the stack.
     */
    void add(Widget* widget) {
        children.push_back(widget);
        dirty = true;
    }

    /**
     * @brief Add one or more child widgets (pointer or reference forms).
     */
    template<typename... Ts>
    void add(Ts&&... widgets) {
        (add_widget(std::forward<Ts>(widgets)), ...);
    }

private:
    void add_widget(Widget* w) { add(w); }
    void add_widget(Widget& w) { add(&w); }

public:
    /**
     * @brief Set stack position (top-left).
     */
    void setPosition(float x, float y) override {
        if (xPos != x || yPos != y) {
            xPos = x;
            yPos = y;
            dirty = true;
        }
    }

    /**
     * @brief Get total stack dimensions including padding.
     */
    sf::Vector2f getDimensions() override {
        return sf::Vector2f(
            std::max(cachedWidth, explicitWidth) + paddingLeft + paddingRight,
            std::max(cachedHeight, explicitHeight) + paddingTop + paddingBottom
        );
    }

    /**
     * @brief Forward input events to all children.
     */
    void handleEvent(const sf::Event& event, sf::RenderWindow &window) override {
        for (Widget* child : children) {
            child->handleEvent(event, window);
        }
    }

    /**
     * @brief Set spacing between children.
     */
    void setGap(float g) {
        if (gap != g) {
            gap = g;
            dirty = true;
        }
    }

    /**
     * @brief Get current child gap.
     */
    float getGap() const { return gap; }

    /**
     * @brief Set main-axis content alignment.
     */
    void setJustifyContent(StackJustify value) {
        if (justify != value) {
            justify = value;
            dirty = true;
        }
    }

    /**
     * @brief Set main-axis alignment from string (`start|center|end`).
     */
    void setJustifyContent(const std::string& value) {
        setJustifyContent(parseJustifyOrFallback(value));
    }

    /**
     * @brief Set cross-axis child alignment.
     */
    void setAlignItems(StackAlign value) {
        if (align != value) {
            align = value;
            dirty = true;
        }
    }

    /**
     * @brief Set cross-axis alignment from string (`start|center|end`).
     */
    void setAlignItems(const std::string& value) {
        setAlignItems(parseAlignOrFallback(value));
    }

    /**
     * @brief Set explicit content size used for alignment calculations.
     */
    void setSize(float width, float height) {
        if (explicitWidth != width || explicitHeight != height) {
            explicitWidth = width;
            explicitHeight = height;
            dirty = true;
        }
    }

    /**
     * @brief Set explicit content width.
     */
    void setWidth(float width) {
        if (explicitWidth != width) {
            explicitWidth = width;
            dirty = true;
        }
    }

    /**
     * @brief Set explicit content height.
     */
    void setHeight(float height) {
        if (explicitHeight != height) {
            explicitHeight = height;
            dirty = true;
        }
    }

    /**
     * @brief Set uniform padding on all sides.
     */
    void setPadding(float p) {
        paddingLeft = p;
        paddingRight = p;
        paddingTop = p;
        paddingBottom = p;
        
        dirty = true;
    }

    /**
     * @brief Set horizontal and vertical padding.
     */
    void setPadding(float horizontal, float vertical) {
        paddingLeft = horizontal;
        paddingRight = horizontal;

        paddingTop = vertical;
        paddingBottom = vertical;

        dirty = true;
    }

    /**
     * @brief Set side-specific padding.
     * @param left Left padding.
     * @param right Right padding.
     * @param top Top padding.
     * @param bottom Bottom padding.
     */
    void setPadding(float left, float right, float top, float bottom) {
        paddingLeft = left;
        paddingRight = right;
        paddingTop = top;
        paddingBottom = bottom;

        dirty = true;
    }

    /**
     * @brief Set container background color.
     */
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

/** @brief Horizontal stack helper (`StackDirection::Horizontal`). */
class HStack : public Stack {
public:
    HStack(float gap = 0) : Stack(StackDirection::Horizontal, gap) {}
};

/** @brief Vertical stack helper (`StackDirection::Vertical`). */
class VStack : public Stack {
public:
    VStack(float gap = 0) : Stack(StackDirection::Vertical, gap) {}
};
