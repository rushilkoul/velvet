#include <SFML/System/Vector2.hpp>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <functional>

class Button : public Widget {
    sf::Texture defaultTexture;
    sf::Texture hoverTexture;
    sf::Texture clickTexture;

    sf::Sprite sprite;
    sf::Text text;

    sf::Color primaryColor;
    sf::Color hoverColor;
    sf::Color clickColor;
    sf::Color borderColor;
    
    int borderThickness;

    bool hovered;
    bool clicked;

    float width, height;

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    std::function<void()> onclick;
    
    void render(sf::RenderWindow &window) override;
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;
    Button(float width=100, float height=50, std::string label="button", sf::Color borderColor = sf::Color::White, int borderThickness = 0);
    Button(const Button& other);
    void setPosition(float x, float y) override;
    sf::Vector2<float> getDimensions() override;
};
