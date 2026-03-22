#include <SFML/System/Vector2.hpp>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>

class Label : public Widget {
private:
    sf::Text LText;
    sf::RectangleShape labelBackground;
    sf::Font font;

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;

public:
    void render(sf::RenderWindow &window) override;
    void setPosition(float x, float y) override;
    sf::Vector2f getDimensions() override;
    Label(std::string text, int fontSize = 20);
    void setText(const std::string txt);

    void setLineSpacing(float spacingFactor) { LText.setLineSpacing(spacingFactor); }
};
