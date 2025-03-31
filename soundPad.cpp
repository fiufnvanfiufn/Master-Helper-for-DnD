#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "soundPad.hpp"
#include "button/button.hpp"


void runSoundPad(sf::Font& font) {
    sf::RenderWindow soundPad(sf::VideoMode(600, 900), L"Саундпад");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/soundPadBackground.png")) {
        return;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(600.f / backgroundTexture.getSize().x,
                        900.f / backgroundTexture.getSize().y);

    button::Button whisperButton(0, 50, "MagicButton", L"Шёпот", font);

    sf::Music whisper;
    if (!whisper.openFromFile("assets/soundEffects/whisper.mp3")) {
        return;
    }

    while (soundPad.isOpen()) {
        sf::Event event;
        while (soundPad.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                whisper.stop();
                soundPad.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (whisperButton.isClicked(mousePos)) {
                    whisper.play();
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(soundPad);
        whisperButton.update(sf::Vector2f(mouse));

        soundPad.clear();
        soundPad.draw(background);
        whisperButton.draw(soundPad);
        soundPad.display();
    }
}
