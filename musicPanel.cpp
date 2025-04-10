#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "musicPanel.hpp"
#include "button/button.hpp"
#include <vector>

void runMusicPanel(sf::Font& font) {
    sf::RenderWindow musicPanel(sf::VideoMode(600, 1000), L"Музыкальная панель");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/musicPanelBackground.png")) {
        return;
    }

    sf::Sprite background(backgroundTexture);
    background.setScale(600.f / backgroundTexture.getSize().x,
                        1000.f / backgroundTexture.getSize().y);

    button::MusicThemeButton tavernMusicButton(30, 200, "TavernButton", L"Таверна", font, "tavern");
    button::MusicThemeButton overWorldMusicButton(300, 200, "OverWorldButton", L"Верхний мир", font, "overWorld");
    button::MusicThemeButton normalBattleMusicButton(30, 350, "NormalBattleButton", L"Обычная битва", font, "normalBattle");
    button::MusicThemeButton bossBattleMusicButton(300, 350, "BossBattleButton", L"Битва с боссом   ", font, "bossMusic");


    std::vector<button::MusicThemeButton*> buttons = {
        &tavernMusicButton,
        &overWorldMusicButton,
        &normalBattleMusicButton,
        &bossBattleMusicButton
    };

    while (musicPanel.isOpen()) {
        sf::Event event;
        while (musicPanel.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                musicPanel.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (button::MusicThemeButton* button : buttons) {
                    if (button->isClicked(mousePos)) {
                        button->playOrStop();
                    }
                }
            }
        }

        sf::Vector2i mouse = sf::Mouse::getPosition(musicPanel);
        for (button::MusicThemeButton* button : buttons) {
            button->update(sf::Vector2f(mouse));
        }

        musicPanel.clear();
        musicPanel.draw(background);
        for (button::MusicThemeButton* button : buttons) {
            button->draw(musicPanel);
        }
        musicPanel.display();
    }
}
