#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>
#include <variant>
#include <velvet/base/Widget.hpp>
#include <SFML/Graphics/Color.hpp>

class InputField : public Widget {
private:
    sf::Text textField;
    sf::Text placeholderText;

    sf::Font font;
    sf::RectangleShape container;

    sf::View clipView;
    sf::View ogView;

    float width;
    bool focused;

    std::string type;

    std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styles = {
        {"fontPath", "src/assets/AdwaitaSans-Regular.ttf"},
        {"fontSize", 20.f},
        {"letterSpacing", 1.f},
        {"fontColor", 0x000000FFu},
        {"outlineColor", 0x000000FFu},
        {"activeOutlineColor", 0x0288D1FFu},
        {"backgroundColor", 0xFFFFFFFFu},
        {"placeholderColor", 0x6E6E6EFFu},
        {"width", 200.f}
    };

    void draw(sf::RenderWindow &window) override;
    void update(sf::RenderWindow &window) override;
    void drawText(sf::Text, sf::RenderWindow &window);
    void updateScroll();
public:
    std::string content;
    std::string placeholder;
    void render(sf::RenderWindow &window) override;
    void setPosition(float x, float y) override;
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;
    sf::Vector2f getDimensions() override;
    InputField(std::string placeholder = "", std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling = {});

    void overrideStyling(std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling);
};
