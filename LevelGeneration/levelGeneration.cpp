#include "levelGeneration.hpp"

room::~room() {
    if (Room != nullptr) {
        for (int i = 0; i < _roomWidth; ++i) {
            delete[] Room[i];
        }
        delete[] Room;
        Room = nullptr;
    }
}

void room::SetRoomWidth(int roomWidth) {
    _roomWidth = roomWidth;
}

void room::SetRoomLength(int roomLength) {
    _roomLength = roomLength;
}

void room::SetTorchesInRoom(int numberOfTorchersRoom) {
    _numberOfTorchersRoom = numberOfTorchersRoom;
}

void room::SetRoom() {
    if (Room != nullptr) {
        for (int i = 0; i < _roomWidth; ++i) {
            delete[] Room[i];
        }
        delete[] Room;
        Room = nullptr;
    }

    Room = new Tile**[_roomWidth];
    for (int i = 0; i < _roomWidth; ++i) {
        Room[i] = new Tile*[_roomLength];
    }

    for (int i = 0; i < _roomWidth; ++i) {
        for (int j = 0; j < _roomLength; ++j) {
            if (i == _roomWidth - 1) {
                Room[i][j] = &lowerWallTile;
            } else if(i == 0) {
                Room[i][j] = &upperWallTile;
            } else if(j == _roomLength - 1) {
                Room[i][j] = &rightWallTile;
            } else if (j == 0){
                Room[i][j] = &leftWallTile;
            } else {
                Room[i][j] = &floorTile;
            }
        }
    }
}

void room::PutTorchesInRoom() {
    int errorRigthWall = RandomGenerator::getRandomNumber(-1, 1);
    int errorLeftWall = RandomGenerator::getRandomNumber(-1, 1);

    if (_numberOfTorchersRoom == 1) {
        Room[_roomWidth / 2 + errorLeftWall - 1][1] = &leftTorchTile;

        Room[_roomWidth / 2 + errorRigthWall - 1][_roomLength - 2] = &rightTorchTile;
    }

    if (_numberOfTorchersRoom == 2) {
        Room[_roomWidth / 3 + errorLeftWall - 1][1] = &leftTorchTile;
        Room[_roomWidth / 3 * 2 + errorLeftWall - 1][1] = &leftTorchTile;

        Room[_roomWidth / 3 + errorRigthWall - 1][_roomLength - 2] = &rightTorchTile;
        Room[_roomWidth / 3 * 2 + errorRigthWall - 1][_roomLength - 2] = &rightTorchTile;
    }

    if (_numberOfTorchersRoom == 3) {
        Room[_roomWidth / 2][1] = &leftTorchTile;
        Room[_roomWidth / 4 + errorLeftWall][1] = &leftTorchTile;
        Room[_roomWidth / 5 * 4 + errorLeftWall + 1][1] = &leftTorchTile;

        Room[_roomWidth / 2][_roomLength - 2] = &rightTorchTile;
        Room[_roomWidth / 4 + errorRigthWall][_roomLength - 2] = &rightTorchTile;
        Room[_roomWidth / 4 * 3 + errorRigthWall + 1][_roomLength - 2] = &rightTorchTile;
    }
}

void room::print() {
    for (int i = 0; i < _roomWidth; ++i) {
        for (int j = 0; j < _roomLength; ++j) {
            std::cout << '[';
            Room[i][j]->Print();
            std::cout  << ']';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

RoomBuilder::RoomBuilder() {
    ex = new room();
}

room* RoomBuilder::GetRoom() {
    return ex;
}

room* Director::CreateRoom(RoomBuilder& builder) {
    builder.SetRoomLength();
    builder.SetRoomWidth();
    builder.SetTorchesInRoom();
    builder.GetRoom()->SetRoom();
    builder.GetRoom()->PutTorchesInRoom();
    return builder.GetRoom();
}
