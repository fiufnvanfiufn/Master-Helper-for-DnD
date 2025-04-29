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

#include "LevelGeneration/levelGeneration.hpp"

int main(int, char**) {
    Director a;

    LargeRoomBuilder LargeRoomBuilder;
    room* LargeRoom = a.CreateRoom(LargeRoomBuilder);

    LargeRoom->print();
}