#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Window");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/pictures/backgrounds/background.jpg")) {
        return -1;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale(
        800.f / backgroundTexture.getSize().x,
        600.f / backgroundTexture.getSize().y
    );

    // Первая кнопка (открывает второе окно)
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(300, 275);

    sf::Font font;
    font.loadFromFile("assets/textStyles/Kereru.ttf");

    sf::Text buttonText(u8"Open music", font, 20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(325, 285);

    bool secondWindowOpen = false;
    sf::RenderWindow secondWindow;

    // Кнопка во втором окне (для запуска музыки)
    sf::RectangleShape musicButton(sf::Vector2f(200, 50));
    musicButton.setFillColor(sf::Color::Red);
    musicButton.setPosition(100, 125);

    sf::Text musicButtonText("Play music", font, 20);
    musicButtonText.setFillColor(sf::Color::White);
    musicButtonText.setPosition(125, 135);

    sf::Music music;
    if (!music.openFromFile("assets/music/music.ogg")) {
        return -1; // Ошибка загрузки
    }

    while (window.isOpen())
    {
        // Главное окно
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (button.getGlobalBounds().contains(mousePos))
                {
                    secondWindow.create(sf::VideoMode(400, 300), "Second Window");
                    secondWindowOpen = true;
                }
            }
        }

        // Второе окно (с кнопкой музыки)
        if (secondWindowOpen)
        {
            sf::Event secondEvent;
            while (secondWindow.pollEvent(secondEvent))
            {
                if (secondEvent.type == sf::Event::Closed)
                {
                    secondWindow.close();
                    music.stop();
                    secondWindowOpen = false;
                }

                if (secondEvent.type == sf::Event::MouseButtonPressed && secondEvent.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos(secondEvent.mouseButton.x, secondEvent.mouseButton.y);
                    if (musicButton.getGlobalBounds().contains(mousePos))
                    {
                        music.play(); // Запуск музыки
                    }
                }
            }
        }

        // Рисуем первое окно
        window.clear();
        window.draw(background);
        window.draw(button);
        window.draw(buttonText);
        window.display();

        // Рисуем второе окно
        if (secondWindowOpen)
        {
            secondWindow.clear(sf::Color::Black);
            secondWindow.draw(musicButton);
            secondWindow.draw(musicButtonText);
            secondWindow.display();
        }
    }

    return 0;
}
