#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "soundPad.hpp"
#include "button/button.hpp"
#include <vector>

void runSoundPad(sf::Font& font) {
    sf::RenderWindow soundPad(sf::VideoMode(600, 1000), L"Саундпад");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/soundPadBackground.png")) {
        return;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(600.f / backgroundTexture.getSize().x,
                        1000.f / backgroundTexture.getSize().y);

    button::SoundEffectButton whisperButton(20, 50, "MagicButton",  L"Шёпот", font, "Whisper.mp3");
    button::SoundEffectButton armorHitButton(20, 170, "MagicButton", L"Удар в броню", font, "SwordToArmor.ogg");
    button::SoundEffectButton swordMissButton(20, 290, "MagicButton", L"Промах мечом", font, "SwordMiss.ogg");
    button::SoundEffectButton swordHitButton(20, 410, "MagicButton", L"Попадание мечом", font, "SwordFleshHit.ogg");
    button::SoundEffectButton swordClashButton(20, 530, "MagicButton", L"Столкновение мечей", font, "SwordClash.ogg");
    button::SoundEffectButton arrowHitButton(20, 650, "MagicButton", L"Попадание стрелой", font, "ArrowHit.ogg");
    button::SoundEffectButton wolfHowlButton(20, 770, "MagicButton", L"Вой волка", font, "WolfHowl.ogg");
    button::SoundEffectButton stickCrackButton(270, 50, "MagicButton", L"Треск ветки", font, "StickCrack.ogg");
    button::SoundEffectButton fireballButton(270, 170, "MagicButton", L"Фаербол", font, "FireBall.ogg");
    button::SoundEffectButton iceAttackButton(270, 290, "MagicButton", L"Атака льдом", font, "IceAttack.ogg");
    button::SoundEffectButton caveSoundButton(270, 410, "MagicButton", L"Эхо пещеры", font, "CaveSound1.ogg");
    button::SoundEffectButton corruptedRoarButton(270, 530, "MagicButton", L"Рык нечисти", font, "CorruptedRoar.ogg");
    button::SoundEffectButton dangerousRoarButton(270, 650, "MagicButton", L"Рык чудовища", font, "BigBeastRoar.ogg");
    button::SoundEffectButton dragonRoarButton(270, 770, "MagicButton", L"Рёв дракона", font, "VeryDangerousRoar.ogg");

    std::vector<button::SoundEffectButton*> buttons = {
        &whisperButton, &armorHitButton, &swordMissButton,
        &swordHitButton, &swordClashButton, &arrowHitButton,
        &stickCrackButton, &fireballButton, &iceAttackButton,
        &caveSoundButton, &corruptedRoarButton, &dangerousRoarButton,
        &wolfHowlButton, &dragonRoarButton
    };

    while (soundPad.isOpen()) {
        sf::Event event;
        while (soundPad.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                soundPad.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (button::SoundEffectButton* button : buttons) {
                    if (button->isClicked(mousePos)) {
                        button->play();
                    }
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(soundPad);
        for (button::SoundEffectButton* button : buttons) {
            button->update(sf::Vector2f(mouse));
        }

        soundPad.clear();
        soundPad.draw(background);
        for (button::SoundEffectButton* button : buttons) {
            button->draw(soundPad);
        }
        soundPad.display();
    }
}
