#include "LevelGeneration/levelGeneration.hpp"

int main(int, char**) {
    Director a;

    SmallRoomBuilder largeRoomBuilder;
    room* LargeRoom = a.CreateRoom(largeRoomBuilder);

    LargeRoom->print();
}
