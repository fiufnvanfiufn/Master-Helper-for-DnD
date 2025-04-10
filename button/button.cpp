#include "button.hpp"

namespace button {
Button::Button(float x, float y, const std::string& type, const std::wstring& text, sf::Font& font) {
    std::map<std::string, std::string> texturePaths = {
        {"DragonButton", "assets/pictures/buttons/DragonButton.png"},
        {"MusicButton",  "assets/pictures/buttons/MusicButton.png" },
        {"MagicButton",  "assets/pictures/buttons/MagicButton.png" },
        {"TavernButton", "assets/pictures/buttons/TavernButton.png"},
        {"OverWorldButton", "assets/pictures/buttons/OverWorldButton.png"},
        {"NormalBattleButton", "assets/pictures/buttons/NormalBattleButton.png"},
        {"BossBattleButton", "assets/pictures/buttons/BossBattleButton.png"}
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
        label.setCharacterSize(36);
        clickableArea = sf::FloatRect(pos.x + 40, pos.y + 140, 360, 120);
        label.setFillColor(sf::Color::White);
    } else if (type == "MusicButton") {
        sprite.setScale(0.35f, 0.2f);
        label.setCharacterSize(46);
        clickableArea = sf::FloatRect(pos.x + 40, pos.y + 40, 280, 120);
        label.setFillColor(sf::Color::White);
    } else if (type == "MagicButton") {
        sprite.setScale(0.20f, 0.15f);
        label.setCharacterSize(24);
        clickableArea = sf::FloatRect(pos.x + 40, pos.y + 40, 200, 70);
        label.setFillColor(sf::Color::White);
    } else if (type == "TavernButton") {
        sprite.setScale(0.2f, 0.2f);
        label.setCharacterSize(32);
        clickableArea = sf::FloatRect(pos.x, pos.y, 250, 150);
        label.setFillColor(sf::Color::White);
    } else if (type == "OverWorldButton") {
        sprite.setScale(0.4f, 0.4f);
        label.setCharacterSize(32);
        clickableArea = sf::FloatRect(pos.x, pos.y, 250, 150);
        label.setFillColor(sf::Color::White);
    } else if (type == "NormalBattleButton") {
        sprite.setScale(0.18f, 0.18f);
        label.setCharacterSize(32);
        clickableArea = sf::FloatRect(pos.x, pos.y, 250, 150);
        label.setFillColor(sf::Color::White);
    } else if (type == "BossBattleButton") {
        sprite.setScale(0.2f, 0.2f);
        label.setCharacterSize(32);
        clickableArea = sf::FloatRect(pos.x, pos.y, 250, 150);
        label.setFillColor(sf::Color::White);
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

MusicThemeButton::MusicThemeButton(float x, float y, std::string type, const std::wstring& text, sf::Font& font, const std::string& folder)
    : Button(x, y, type, text, font), musicFolder("assets/music/" + folder), isPlaying(false) {
    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(musicFolder)) {
        if (entry.path().extension() == ".ogg" || entry.path().extension() == ".mp3") {
            playlist.push_back(entry.path().string());
        }
    }
}

void MusicThemeButton::playOrStop() {
    if (isPlaying) {
        music.stop();
        isPlaying = false;
    } else {
        playRandom();
        isPlaying = true;
    }
}

void MusicThemeButton::update(const sf::Vector2f& mousePos) {
    Button::update(mousePos);
    if (isPlaying && music.getStatus() == sf::Music::Stopped) {
        playRandom();
    }
}

void MusicThemeButton::playRandom() {
    if (!playlist.empty()) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, playlist.size() - 1);
        std::string selected = playlist[dis(gen)];

        if (!music.openFromFile(selected)) {
            throw std::runtime_error("Не удалось загрузить музыкальный трек: " + selected);
        }
        music.play();
    }
}

}  // namespace button
