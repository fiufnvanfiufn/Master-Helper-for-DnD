#include <SFML/Graphics.hpp>
#include <thread>
#include <SFML/Audio.hpp>
#include "menu.hpp"
#include "soundPad.hpp"
#include "button/button.hpp"
#include "musicPanel.hpp"
#include "levelGenerator.hpp"

int runMainMenu(sf::Font& font) {
    sf::RenderWindow menu(sf::VideoMode(1920, 1080), L"Меню");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/menuBackground.png")) {
        return -1;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale(1920.f / backgroundTexture.getSize().x,
                        1080.f / backgroundTexture.getSize().y);

    button::Button soundPadOpenButton(50, 600, "DragonButton", L"Саундпад", font);
    button::Button musicPanelOpenButton(750, 600, "DragonButton", L"Музыкальная панель", font);
    button::Button levelGeneratorOpenButton(1500, 600, "DragonButton", L"Генератор комнат", font);


    while (menu.isOpen()) {
        sf::Event event;
        while (menu.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                menu.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (soundPadOpenButton.isClicked(mousePos)) {
                    std::thread soundPadThread([&font]() {
                        runSoundPad(font);
                    });
                    soundPadThread.detach();
                } else if (musicPanelOpenButton.isClicked(mousePos)) {
                    std::thread musicPanelThread([&font]() {
                        runMusicPanel(font);
                    });
                    musicPanelThread.detach();
                } else if (levelGeneratorOpenButton.isClicked(mousePos)) {
                    std::thread levelGeneratorThread([&font]() {
                        RunLevelGenerator(font);
                    });
                    levelGeneratorThread.detach();
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(menu);
        soundPadOpenButton.update(sf::Vector2f(mouse));
        musicPanelOpenButton.update(sf::Vector2f(mouse));
        levelGeneratorOpenButton.update(sf::Vector2f(mouse));

        menu.clear();
        menu.draw(background);
        musicPanelOpenButton.draw(menu);
        soundPadOpenButton.draw(menu);
        levelGeneratorOpenButton.draw(menu);
        menu.display();
    }
    return 0;
}
