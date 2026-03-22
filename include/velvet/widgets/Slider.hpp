#include <SFML/System/Vector2.hpp>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <functional>

class Slider : public Widget {
private:
    sf::RectangleShape active_part;
    sf::RectangleShape inactive_part;
    sf::RectangleShape thumb;

    float height, width;
    float from, to;
    float sliderValue;
    float thickness = 20;
    float length;

    bool thumbBeingPressed;
    bool hovered;

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    std::function<void(float)> onchange;

    void render(sf::RenderWindow &window) override;
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getDimensions() override;
    Slider(float size, float from = 0.0f, float to = 1.0f);
    void changeValue(float value);
    float getValue();
};
