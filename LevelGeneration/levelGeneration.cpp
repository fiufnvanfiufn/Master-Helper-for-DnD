#include "levelGeneration.hpp"

room::~room() {
    for (int i = 0; i < _roomWidth; ++i) {
        for (int j = 0; j < _roomLength; ++j) {
            delete Room[i][j];
            Room[i][j] = nullptr;
        }
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
    Room.resize(_roomWidth);
    for (auto& row : Room) {
        row.resize(_roomLength);
    }
    for (int i = 0; i < _roomWidth; ++i) {
        for (int j = 0; j < _roomLength; ++j) {
            if (i == _roomWidth - 1 && j != 0 && j != _roomLength - 1) {
                Room[i][j] = new LowerWallTile;
            } else if(i == 0 && j != 0 && j != _roomWidth - 1) {
                Room[i][j] = new UpperWallTile;
            } else if(j == _roomLength - 1 && i != 0 && i != _roomWidth - 1) {
                Room[i][j] = new RightWallTile;
            } else if (j == 0 && i != 0 && i != _roomWidth - 1){
                Room[i][j] = new LeftWallTile;
            } else if (i == 0 && j != 0 && j != _roomLength - 1) {
                Room[i][j] = new FloorTile;
            } else if (i == _roomWidth - 1 && j == 0) {
                Room[i][j] = new LeftLowerWallCorner;
            } else if (i == 0 && j == 0) {
                Room[i][j] = new LeftUpperWallCorner;
            } else if (i == 0 && j == _roomLength - 1) {
                Room[i][j] = new RightUpperWallCorner;
            } else if (i == _roomWidth - 1 && j == _roomLength - 1) {
                Room[i][j] = new RightLowerWallCorner;
            }
        }
    }
}

void room::PutTorchesInRoom() {
    int errorRigthWall = RandomGenerator::getRandomNumber(-1, 1);
    int errorLeftWall = RandomGenerator::getRandomNumber(-1, 1);

    if (_numberOfTorchersRoom == 1) {
        Room[_roomWidth / 2 + errorLeftWall - 1][1] = new LeftTorchTile;

        Room[_roomWidth / 2 + errorRigthWall - 1][_roomLength - 2] = new RightTorchTile;
    }

    if (_numberOfTorchersRoom == 2) {
        Room[_roomWidth / 3 + errorLeftWall - 1][1] = new LeftTorchTile;
        Room[_roomWidth / 3 * 2 + errorLeftWall - 1][1] = new LeftTorchTile;

        Room[_roomWidth / 3 + errorRigthWall - 1][_roomLength - 2] = new RightTorchTile;
        Room[_roomWidth / 3 * 2 + errorRigthWall - 1][_roomLength - 2] = new RightTorchTile;
    }

    if (_numberOfTorchersRoom == 3) {
        Room[_roomWidth / 2][1] = new LeftTorchTile;
        Room[_roomWidth / 4 + errorLeftWall][1] = new LeftTorchTile;
        Room[_roomWidth / 5 * 4 + errorLeftWall + 1][1] = new LeftTorchTile;

        Room[_roomWidth / 2][_roomLength - 2] = new RightTorchTile;
        Room[_roomWidth / 4 + errorRigthWall][_roomLength - 2] = new RightTorchTile;
        Room[_roomWidth / 4 * 3 + errorRigthWall + 1][_roomLength - 2] = new RightTorchTile;
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
