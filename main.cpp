#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "button/button.hpp"
#include "menu.hpp"

int main() {
    setlocale(LC_ALL, "Russian");
    sf::Font font;
    if (!font.loadFromFile("assets/textStyles/Kereru.ttf")) {
        return -1;
    }

    return runMainMenu(font);
}
