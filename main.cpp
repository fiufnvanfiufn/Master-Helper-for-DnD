#include "LevelGeneration/levelGeneration.hpp"

int main(int, char**) {
    Director a;

    LargeRoomBuilder largeRoomBuilder;
    room* LargeRoom = a.CreateRoom(largeRoomBuilder);

    LargeRoom->print();
}
