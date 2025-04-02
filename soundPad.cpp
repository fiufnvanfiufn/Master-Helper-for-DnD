#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "soundPad.hpp"
#include "button/button.hpp"
#include <vector>

void runSoundPad(sf::Font& font) {
    sf::RenderWindow soundPad(sf::VideoMode(600, 900), L"Саундпад");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/soundPadBackground.png")) {
        return;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(600.f / backgroundTexture.getSize().x,
                        900.f / backgroundTexture.getSize().y);

    button::SoundEffectButton whisperButton(0, 50, "MagicButton",  L"Шёпот", font, "Whisper.mp3");
    button::SoundEffectButton armorHitButton(0, 170, "MagicButton", L"Удар в броню", font, "SwordToArmor.ogg");
    button::SoundEffectButton swordMissButton(0, 290, "MagicButton", L"Промах мечом", font, "SwordMiss.ogg");
    button::SoundEffectButton swordHitButton(0, 410, "MagicButton", L"Попадание мечом", font, "SwordFleshHit.ogg");
    button::SoundEffectButton swordClashButton(0, 530, "MagicButton", L"Столкновение мечей", font, "SwordClash.ogg");
    button::SoundEffectButton arrowHitButton(0, 650, "MagicButton", L"Попадание стрелой", font, "ArrowHit.ogg");

    std::vector<button::SoundEffectButton*> buttons = {
        &whisperButton, &armorHitButton, &swordMissButton,
        &swordHitButton, &swordClashButton, &arrowHitButton
    };

    while (soundPad.isOpen()) {
        sf::Event event;
        while (soundPad.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                soundPad.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (auto* b : buttons) {
                    if (b->isClicked(mousePos)) {
                        b->play();
                    }
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(soundPad);
        for (auto* b : buttons) {
            b->update(sf::Vector2f(mouse));
        }

        soundPad.clear();
        soundPad.draw(background);
        for (auto* b : buttons) {
            b->draw(soundPad);
        }
        soundPad.display();
    }
}
