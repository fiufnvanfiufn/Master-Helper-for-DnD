#include "button.hpp"

namespace button {
    Button::Button(float x, float y, const std::string& type, const std::wstring& text, sf::Font& font) {
        // Загружаем нужную текстуру по типу кнопки
        std::map<std::string, std::string> texturePaths = {
            {"DragonButton", "assets/pictures/buttons/DragonButton.png"},
            {"MusicButton", "assets/pictures/buttons/MusicButton.png"}
        };

        if (!texture.loadFromFile(texturePaths[type])) {
            throw std::runtime_error("Не удалось загрузить текстуру кнопки: " + type);
        }

        sprite.setTexture(texture);
        sprite.setPosition(x, y);

        configureClickableArea(type);

        // Текст
        label.setFont(font);
        label.setString(text);

        sf::FloatRect bounds = label.getLocalBounds();
        label.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

        // Центрирование текста относительно видимого размера кнопки
        sf::FloatRect spriteBounds = sprite.getGlobalBounds();
        label.setPosition(spriteBounds.left + spriteBounds.width / 2.f,
                          spriteBounds.top + spriteBounds.height / 2.f);
    }

    void Button::configureClickableArea(const std::string& type) {
        sf::Vector2f pos = sprite.getPosition();
        if (type == "DragonButton") {
            sprite.setScale(0.4f, 0.4f);
            label.setCharacterSize(28);
            clickableArea = sf::FloatRect(pos.x + 40, pos.y + 140, 360, 120);
            label.setFillColor(sf::Color::White);
        } else if (type == "MusicButton") {
            sprite.setScale(0.2f, 0.2f);
            label.setCharacterSize(20);
            clickableArea = sf::FloatRect(pos.x + 20, pos.y + 80, 180, 60);
            label.setFillColor(sf::Color::Black);
        } else {
            clickableArea = sprite.getGlobalBounds();
        }
    }

    void Button::draw(sf::RenderWindow& window) {
        window.draw(sprite);
        window.draw(label);
    }

    bool Button::isClicked(const sf::Vector2f& mousePos) const {
        return clickableArea.contains(mousePos);
    }

    void Button::update(const sf::Vector2f& mousePos) {
        if (clickableArea.contains(mousePos)) {
            if (!hovered) {
                hovered = true;
                sprite.setColor(sf::Color(255, 200, 100));
            }
        } else if (hovered) {
                hovered = false;
                sprite.setColor(sf::Color(255, 255, 255));
        }
    }

}
