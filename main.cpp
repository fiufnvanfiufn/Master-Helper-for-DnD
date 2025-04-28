#include "LevelGeneration/levelGeneration.hpp"

int main(int, char**) {
    Director a;

    LargeRoomBuilder LargeRoomBuilder;
    room* LargeRoom = a.CreateRoom(LargeRoomBuilder);

    LargeRoom->print();
}
