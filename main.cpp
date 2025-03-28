#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.hpp"

using namespace button;

int main() {
    setlocale(LC_ALL, "Russian");
    sf::RenderWindow menu(sf::VideoMode(1920, 1080), L"Меню");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/background.png")) {
        return -1;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale(1920.f / backgroundTexture.getSize().x, 1080.f / backgroundTexture.getSize().y);

    sf::Font font;
    if (!font.loadFromFile("assets/textStyles/Kereru.ttf")) {
        return -1;
    }

    Button dragonButton(50, 600, "DragonButton", L"Открыть саундпад", font);
    Button whisperButton(0, 0, "MusicButton", L"Шёпот", font);

    bool soundPadOpen = false;
    sf::RenderWindow soundPad;
    sf::Music whisper;
    if (!whisper.openFromFile("assets/soundEffects/Whisper.mp3")) {
        return -1;
    }

    while (menu.isOpen()) {
        sf::Event event;
        while (menu.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                menu.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (dragonButton.isClicked(mousePos)) {
                    soundPad.create(sf::VideoMode(400, 300), L"Саундпад");
                    soundPadOpen = true;
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(menu);
        dragonButton.update(sf::Vector2f(mouse));

        if (soundPadOpen) {
            sf::Event secondEvent;
            while (soundPad.pollEvent(secondEvent)) {
                if (secondEvent.type == sf::Event::Closed) {
                    soundPad.close();
                    whisper.stop();
                    soundPadOpen = false;
                }

                if (secondEvent.type == sf::Event::MouseButtonPressed && secondEvent.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(secondEvent.mouseButton.x, secondEvent.mouseButton.y);
                    if (whisperButton.isClicked(mousePos)) {
                        whisper.play();
                    }
                }
            }

            sf::Vector2i soundPadMouse = sf::Mouse::getPosition(soundPad);
            whisperButton.update(sf::Vector2f(soundPadMouse));
        }

        // Главное окно
        menu.clear();
        menu.draw(background);
        dragonButton.draw(menu);
        menu.display();

        // Второе окно
        if (soundPadOpen) {
            soundPad.clear(sf::Color::Black);
            whisperButton.draw(soundPad);
            soundPad.display();
        }
    }

    return 0;
}
