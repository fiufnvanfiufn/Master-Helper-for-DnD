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

    button::SoundEffectButton whisperButton(0, 50, "MagicButton",  L"Шёпот", font, "Whisper.mp3");
    button::SoundEffectButton armorHitButton(0, 170, "MagicButton", L"Удар в броню", font, "SwordToArmor.ogg");
    button::SoundEffectButton swordMissButton(0, 290, "MagicButton", L"Промах мечом", font, "SwordMiss.ogg");
    button::SoundEffectButton swordHitButton(0, 410, "MagicButton", L"Попадание мечом", font, "SwordFleshHit.ogg");
    button::SoundEffectButton swordClashButton(0, 530, "MagicButton", L"Столкновение мечей", font, "SwordClash.ogg");
    button::SoundEffectButton arrowHitButton(0, 650, "MagicButton", L"Попадание стрелой", font, "ArrowHit.ogg");


    while (soundPad.isOpen()) {
        sf::Event event;
        while (soundPad.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                soundPad.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (whisperButton.isClicked(mousePos)) {
                    whisperButton.play();
                }
                if (armorHitButton.isClicked(mousePos)) {
                    armorHitButton.play();
                }
                if (swordMissButton.isClicked(mousePos)) {
                    swordMissButton.play();
                }
                if (swordHitButton.isClicked(mousePos)) {
                    swordHitButton.play();
                }
                if (arrowHitButton.isClicked(mousePos)) {
                    arrowHitButton.play();
                }
                if (swordClashButton.isClicked(mousePos)) {
                    swordClashButton.play();
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(soundPad);
        whisperButton.update(sf::Vector2f(mouse));
        armorHitButton.update(sf::Vector2f(mouse));
        swordMissButton.update(sf::Vector2f(mouse));
        swordHitButton.update(sf::Vector2f(mouse));
        arrowHitButton.update(sf::Vector2f(mouse));
        swordClashButton.update(sf::Vector2f(mouse));

        soundPad.clear();
        soundPad.draw(background);
        armorHitButton.draw(soundPad);
        whisperButton.draw(soundPad);
        arrowHitButton.draw(soundPad);
        swordClashButton.draw(soundPad);
        swordMissButton.draw(soundPad);
        swordHitButton.draw(soundPad);
        soundPad.display();
    }
}
