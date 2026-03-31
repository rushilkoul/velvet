 #pragma once
 #include <SFML/Graphics/RectangleShape.hpp>
 #include <SFML/Graphics/RenderWindow.hpp>
 #include <SFML/Graphics/Text.hpp>
 #include <SFML/System/Vector2.hpp>
 #include <unordered_map>
 #include <variant>
 #include <velvet/base/Widget.hpp>
 #include <SFML/Graphics/Color.hpp>

/**
 * @brief Single-line text input widget with placeholder and basic styling.
 *
 * Supported style keys (`std::unordered_map<std::string, std::variant<unsigned int, float, std::string>>`):
 * - `fontPath` (`std::string`)
 * - `fontSize` (`float`)
 * - `letterSpacing` (`float`)
 * - `fontColor` (`unsigned int`) text color, RGBA hex like `0xRRGGBBAA`
 * - `outlineColor` (`unsigned int`) inactive border color
 * - `activeOutlineColor` (`unsigned int`) active border color when focused
 * - `backgroundColor` (`unsigned int`) input background fill
 * - `placeholderColor` (`unsigned int`) color of the placeholder text
 * - `width` (`float`) logical width of the input box
 */
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
    std::string content;
    std::string placeholder;

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

    /** @brief Render the input field. */
    void render(sf::RenderWindow &window) override;

    /** @brief Set top-left position of the input box. */
    void setPosition(float x, float y) override;

    /** @brief Handle focus changes and text input/backspace events. */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

    /** @brief Get input field dimensions (container bounds). */
    sf::Vector2f getDimensions() override;

    /**
     * @brief Create an input field with optional placeholder and style overrides.
     * @param placeholder Placeholder text to display when empty.
     * @param styling Optional style overrides map; unknown keys are ignored with a warning.
     */
    InputField(std::string placeholder = "", std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling = {});

    /**
     * @brief Apply/override style properties at runtime.
     *
     * Unknown keys are ignored with a warning.
     */
    void overrideStyling(std::unordered_map<std::string, std::variant<unsigned int, float, std::string>> styling);

    //getters
    std::string getContent();
    std::string getPlaceholder();

    //setters
    void setPlaceholder(std::string placeholderString);
};
