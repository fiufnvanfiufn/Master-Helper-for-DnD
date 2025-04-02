#include "button.hpp"

namespace button {
Button::Button(float x, float y, const std::string& type, const std::wstring& text, sf::Font& font) {
    std::map<std::string, std::string> texturePaths = {
        {"DragonButton", "assets/pictures/buttons/DragonButton.png"},
        {"MusicButton",  "assets/pictures/buttons/SoundEffectButton.png" },
        {"MagicButton",  "assets/pictures/buttons/MagicButton.png" }
    };

    if (!texture.loadFromFile(texturePaths[type])) {
        throw std::runtime_error("Не удалось загрузить текстуру кнопки: " + type);
    }

    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    configureClickableArea(type);

    label.setFont(font);
    label.setString(text);

    sf::FloatRect bounds = label.getLocalBounds();
    label.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    label.setPosition(spriteBounds.left + spriteBounds.width / 2.f, spriteBounds.top + spriteBounds.height / 2.f);
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
    } else if (type == "MagicButton") {
        sprite.setScale(0.20f, 0.15f);
        label.setCharacterSize(24);
        clickableArea = sf::FloatRect(pos.x + 40, pos.y + 40, 200, 70);
        label.setFillColor(sf::Color::Blue);
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

SoundEffectButton::SoundEffectButton(float x, float y, std::string type, const std::wstring& text, sf::Font& font, const std::string& soundName)
    : Button(x, y, type, text, font) {
    std::string path = "assets/soundEffects/" + soundName;
    if (!music.openFromFile(path)) {
        throw std::runtime_error("Не удалось загрузить музыку: " + path);
    }
}

void SoundEffectButton::play() {
    music.play();
}
}  // namespace button
