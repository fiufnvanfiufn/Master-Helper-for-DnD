#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelGeneration/levelGeneration.hpp"
#include "levelGenerator.hpp"
#include <iostream>
#include "button/button.hpp"
#include <vector>

void RunLevelGenerator(sf::Font& font) {
    sf::RenderWindow levelGenerator(sf::VideoMode(1000, 1000), L"Генератор комнат");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/levelGeneratorBackground.png")) {
        return;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(1000.f / backgroundTexture.getSize().x,
                        1000.f / backgroundTexture.getSize().y);

    button::Button generateSmallRoomButton(0, 0, "DungeonButton", L"Создать маленькую комнату", font);
    button::Button generateLargeRoomButton(500, 0, "DungeonButton", L"Создать большую комнату", font);

    button::Button yesButton(250, 600, "DungeonButton", L"Да", font);
    button::Button noButton(500, 600, "DungeonButton", L"Нет", font);

    std::vector<button::Button*> buttons = {
        &generateSmallRoomButton,
        &generateLargeRoomButton
    };

    sf::Text questionText;
    questionText.setFont(font);
    questionText.setCharacterSize(50);
    questionText.setFillColor(sf::Color::White);
    questionText.setString(L"Добавить колонны в комнату?");
    questionText.setPosition(200, 500);

    room* currentRoom = nullptr;

    bool buildingComplete = false;
    bool buildingStart = false;

    while (levelGenerator.isOpen()) {
        sf::Event event;
        while (levelGenerator.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                levelGenerator.close();
            }
            if (!buildingStart){
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (generateLargeRoomButton.isClicked(mousePos)) {
                    buildingComplete = false;
                    buildingStart = true;
                    if (currentRoom) { delete currentRoom; currentRoom = nullptr;}
                    Director a;
                    LargeRoomBuilder largeRoomBuilder;
                    currentRoom = a.CreateRoom(largeRoomBuilder);
                } else if (generateSmallRoomButton.isClicked(mousePos)) {
                    buildingComplete = false;
                    buildingStart = true;
                    if (currentRoom)  { delete currentRoom; currentRoom = nullptr;}
                    Director a;
                    SmallRoomBuilder smallRoomBuilder;
                    currentRoom = a.CreateRoom(smallRoomBuilder);
                    }
                }
            } else if (buildingStart) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (yesButton.isClicked(mousePos)) {
                        if (currentRoom) currentRoom->PutColumnsInRoom();
                            buildingComplete = true;
                            buildingStart = false;
                    } else if (noButton.isClicked(mousePos)) {
                        buildingComplete = true;
                        buildingStart = false;
                    }
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(levelGenerator);


        levelGenerator.clear();
        levelGenerator.draw(background);

        if (!buildingStart){
            for (button::Button* button : buttons) {
                button->draw(levelGenerator);
            }
            for (button::Button* button : buttons) {
                button->update(sf::Vector2f(mouse));
            }
        } else {
            levelGenerator.draw(questionText);
            yesButton.draw(levelGenerator);
            noButton.draw(levelGenerator);
            yesButton.update(sf::Vector2f(mouse));
            noButton.update(sf::Vector2f(mouse));
        }


        if (currentRoom) {
            if (buildingComplete) {
                std::cout << "drawing:" << std::endl;
                currentRoom->draw(levelGenerator);
            }

        }

        levelGenerator.display();
    }

    if (currentRoom) delete currentRoom;
}
