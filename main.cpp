#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main() {
    setlocale(LC_ALL, "Russian");
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Main Window");

  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile(
          "assets/pictures/backgrounds/background.png")) {
    return -1;
  }
  sf::Sprite background(backgroundTexture);
  background.setScale(1920.f / backgroundTexture.getSize().x,
                      1080.f / backgroundTexture.getSize().y);

  // Первая кнопка (открывает второе окно)
  sf::Texture dragonButtonTexture;
  if (!dragonButtonTexture.loadFromFile(
          "assets/pictures/buttons/DragonButton.png")) {
    return -1;
  }

  sf::Sprite dragonButtonSprite;
  dragonButtonSprite.setTexture(dragonButtonTexture);
  dragonButtonSprite.setPosition(50, 600);

  dragonButtonSprite.setScale(0.4f, 0.4f);
  sf::Vector2f pos = dragonButtonSprite.getPosition();
  sf::FloatRect clickableArea(pos.x + 40, pos.y + 140, 360, 80);

  sf::Font font;
  font.loadFromFile("assets/textStyles/Kereru.ttf");

  sf::Text buttonText(L"Открыть саундпад", font, 30);
  buttonText.setFillColor(sf::Color::White);
  buttonText.setPosition(pos.x + 100, pos.y + 175);

  bool secondWindowOpen = false;
  sf::RenderWindow secondWindow;

  // Кнопка во втором окне (для запуска музыки)
  sf::Texture whisperButtonTexture;
  if (!whisperButtonTexture.loadFromFile("assets/pictures/buttons/MusicButton.png")) {
    return 1;
  }

  sf::Sprite whisperButtonSprite(whisperButtonTexture);
  whisperButtonSprite.setPosition(0, 0);
  whisperButtonSprite.setScale(0.2f, 0.2f);
  sf::Vector2f pos2 = whisperButtonSprite.getPosition();
  sf::FloatRect whisperClickableArea(pos2.x + 20, pos2.y + 80, 180, 40);

  sf::Text musicButtonText(L"Шёпот", font, 20);
  musicButtonText.setFillColor(sf::Color::White);
  musicButtonText.setPosition(pos2.x + 80,pos2.y + 90);

  sf::Music whisper;
  if (!whisper.openFromFile("assets/soundEffects/whisper.mp3")) {
    return -1; // Ошибка загрузки
  }

  while (window.isOpen()) {
    // Главное окно
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
        if (clickableArea.contains(mousePos)) {
          secondWindow.create(sf::VideoMode(400, 300), "soundPad");
          secondWindowOpen = true;
        }
      }
    }

    // Второе окно (с кнопкой музыки)
    if (secondWindowOpen) {
      sf::Event secondEvent;
      while (secondWindow.pollEvent(secondEvent)) {
        if (secondEvent.type == sf::Event::Closed) {
          secondWindow.close();
          whisper.stop();
          secondWindowOpen = false;
        }

        if (secondEvent.type == sf::Event::MouseButtonPressed &&
            secondEvent.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mousePos(secondEvent.mouseButton.x,
                                secondEvent.mouseButton.y);
          if (whisperClickableArea.contains(mousePos)) {
            whisper.play(); // Запуск музыки
          }
        }
      }
    }

    // Рисуем первое окно
    window.clear();
    window.draw(background);
    window.draw(dragonButtonSprite);
    window.draw(buttonText);
    window.display();

    // Рисуем второе окно
    if (secondWindowOpen) {
      secondWindow.clear(sf::Color::Black);
      secondWindow.draw(whisperButtonSprite);
      secondWindow.draw(musicButtonText);
      secondWindow.display();
    }
  }

  return 0;
}
