#include "levelGenerator.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "LevelGeneration/levelGeneration.hpp"
#include "button/button.hpp"

void RunLevelGenerator(sf::Font& font) {
    sf::RenderWindow levelGenerator(sf::VideoMode(1700, 1080), L"Генератор комнат");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/levelGeneratorBackground.png")) {
        return;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(1700.f / backgroundTexture.getSize().x, 1080.f / backgroundTexture.getSize().y);

    button::Button generateSmallRoomButton(1300, 0, "DungeonButton", L"Создать маленькую комнату", font);
    button::Button generateLargeRoomButton(1300, 700, "DungeonButton", L"Создать большую комнату", font);

    button::Button yesButton(600, 200, "DungeonButton", L"Да", font);
    button::Button noButton(850, 200, "DungeonButton", L"Нет", font);

    std::vector<button::Button*> buttons = { &generateSmallRoomButton, &generateLargeRoomButton };

    sf::Text columnQuestionText;
    columnQuestionText.setFont(font);
    columnQuestionText.setCharacterSize(50);
    columnQuestionText.setFillColor(sf::Color::White);
    columnQuestionText.setString(L"Добавить колонны в комнату?");
    columnQuestionText.setPosition(600, 100);

    sf::Text waterQuestionText;
    waterQuestionText.setFont(font);
    waterQuestionText.setCharacterSize(50);
    waterQuestionText.setFillColor(sf::Color::White);
    waterQuestionText.setString(L"Добавить воду в комнату?");
    waterQuestionText.setPosition(600, 100);

    sf::Text torchesQuestionText;
    torchesQuestionText.setFont(font);
    torchesQuestionText.setCharacterSize(50);
    torchesQuestionText.setFillColor(sf::Color::White);
    torchesQuestionText.setString(L"Добавить факелы в комнату?");
    torchesQuestionText.setPosition(600, 100);

    room* currentRoom = nullptr;

    bool buildingComplete = false;
    bool buildingStart = false;
    bool columnMarkPoint = false;
    bool waterMarkPoint = false;
    bool torchMarkPoint = false;

    while (levelGenerator.isOpen()) {
        sf::Event event;
        while (levelGenerator.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                levelGenerator.close();
            }

            if (!buildingStart) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (generateLargeRoomButton.isClicked(mousePos)) {
                        buildingComplete = false;
                        columnMarkPoint = false;
                        waterMarkPoint = false;
                        torchMarkPoint = true;
                        buildingStart = true;

                        if (currentRoom) {
                            delete currentRoom;
                            currentRoom = nullptr;
                        }

                        Director a;
                        LargeRoomBuilder largeRoomBuilder;
                        currentRoom = a.CreateRoom(largeRoomBuilder);

                    } else if (generateSmallRoomButton.isClicked(mousePos)) {
                        buildingComplete = false;
                        columnMarkPoint = true;
                        waterMarkPoint = false;
                        torchMarkPoint = false;
                        buildingStart = true;

                        if (currentRoom) {
                            delete currentRoom;
                            currentRoom = nullptr;
                        }

                        Director a;
                        SmallRoomBuilder smallRoomBuilder;
                        currentRoom = a.CreateRoom(smallRoomBuilder);
                    }
                }
            } else if (buildingStart) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (yesButton.isClicked(mousePos)) {
                        if (currentRoom) {
                            if (torchMarkPoint) {
                                currentRoom->PutTorchesInRoom();
                                torchMarkPoint = false;
                                waterMarkPoint = true;
                            } else if (waterMarkPoint) {
                                currentRoom->PutWaterInRoom();
                                waterMarkPoint = false;
                                columnMarkPoint = true;
                            } else if (columnMarkPoint) {
                                currentRoom->PutColumnsInRoom();
                                buildingStart = false;
                                buildingComplete = true;
                            }
                        }
                    } else if (noButton.isClicked(mousePos)) {
                        if (columnMarkPoint) {
                            columnMarkPoint = false;
                            waterMarkPoint = true;
                        } else if (waterMarkPoint) {
                            waterMarkPoint = false;
                            torchMarkPoint = true;
                        } else if (torchMarkPoint) {
                            torchMarkPoint = false;
                            buildingStart = false;
                            buildingComplete = true;
                        }
                    }
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(levelGenerator);

        levelGenerator.clear();
        levelGenerator.draw(background);

        if (!buildingStart) {
            for (button::Button* button : buttons) {
                button->draw(levelGenerator);
            }
            for (button::Button* button : buttons) {
                button->update(sf::Vector2f(mouse));
            }
        } else {
            if (columnMarkPoint) {
                levelGenerator.draw(columnQuestionText);
            } else if (waterMarkPoint) {
                levelGenerator.draw(waterQuestionText);
            } else if (torchMarkPoint) {
                levelGenerator.draw(torchesQuestionText);
            }

            yesButton.draw(levelGenerator);
            noButton.draw(levelGenerator);
            yesButton.update(sf::Vector2f(mouse));
            noButton.update(sf::Vector2f(mouse));
        }

        if (currentRoom) {
            if (buildingComplete) {
                currentRoom->draw(levelGenerator);
            }
        }

        levelGenerator.display();
    }

    if (currentRoom)
        delete currentRoom;
}
