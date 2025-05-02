#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelGeneration/levelGeneration.hpp"
#include "levelGenerator.hpp"
#include <iostream>
#include "button/button.hpp"
#include <vector>

void RunLevelGenerator(sf::Font& font) {
    sf::RenderWindow levelGenerator(sf::VideoMode(1000, 1000), L"Музыкальная панель");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/levelGeneratorBackground.png")) {
        return;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(1000.f / backgroundTexture.getSize().x,
                        1000.f / backgroundTexture.getSize().y);

    button::Button generateSmallRoomButton(0, 0, "DungeonButton", L"Создать маленькую комнату", font);
    button::Button generateLargeRoomButton(500, 0, "DungeonButton", L"Создать большую комнату", font);



    std::vector<button::Button*> buttons = {
        &generateSmallRoomButton,
        &generateLargeRoomButton
    };

    while (levelGenerator.isOpen()) {
        sf::Event event;
        while (levelGenerator.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                levelGenerator.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (generateLargeRoomButton.isClicked(mousePos)) {
                    Director a;
                    LargeRoomBuilder largeRoomBuilder;
                    room* LargeRoom = a.CreateRoom(largeRoomBuilder);
                    LargeRoom->print();
                } else if(generateSmallRoomButton.isClicked(mousePos)) {
                    Director a;
                    SmallRoomBuilder smallRoomBuilder;
                    room* smallRoom = a.CreateRoom(smallRoomBuilder);
                    smallRoom->print();
                }
            }

        }

        sf::Vector2i mouse = sf::Mouse::getPosition(levelGenerator);
        for (button::Button* button : buttons) {
            button->update(sf::Vector2f(mouse));
        }

        levelGenerator.clear();
        levelGenerator.draw(background);
        for (button::Button* button : buttons) {
            button->draw(levelGenerator);
        }
        levelGenerator.display();
    }
}
