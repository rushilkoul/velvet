#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>

class Button : public Widget {
    //sf::RectangleShape shape;
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

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    void render(sf::RenderWindow &window) override;
    void handleEvent(const sf::Event &event) override;
    Button(float x, float y, float width, float height, std::string label, sf::Color borderColor = sf::Color::White, int borderThickness = 0);
    
    Button(const Button& other);
};
