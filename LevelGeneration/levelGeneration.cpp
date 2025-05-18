#include "levelGeneration.hpp"

sf::Texture FloorTile::texture;
sf::Texture RightWallTile::texture;
sf::Texture LeftWallTile::texture;
sf::Texture UpperWallTile::texture;
sf::Texture LowerWallTile::texture;
sf::Texture RightTorchTile::texture;
sf::Texture LeftTorchTile::texture;
sf::Texture UpperTorchTile::texture;
sf::Texture LowerTorchTile::texture;
sf::Texture RightUpperWallCorner::texture;
sf::Texture LeftUpperWallCorner::texture;
sf::Texture RightLowerWallCorner::texture;
sf::Texture LeftLowerWallCorner::texture;
sf::Texture Column::texture;


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
    const float TILE_SIZE = 64.f;
    Room.resize(_roomWidth);
    for (auto& row : Room) {
        row.resize(_roomLength);
    }
    for (int i = 0; i < _roomWidth; ++i) {
        for (int j = 0; j < _roomLength; ++j) {
            float x = j * TILE_SIZE;
            float y = i * TILE_SIZE;
            if (i == _roomWidth - 1 && j != 0 && j != _roomLength - 1) {
                Room[i][j] = new LowerWallTile(x, y);
            } else if(i == 0 && j != 0 && j != _roomWidth - 1) {
                Room[i][j] = new UpperWallTile(x, y);
            } else if(j == _roomLength - 1 && i != 0 && i != _roomWidth - 1) {
                Room[i][j] = new RightWallTile(x, y);
            } else if (j == 0 && i != 0 && i != _roomWidth - 1){
                Room[i][j] = new LeftWallTile(x, y);
            } else if (i == 0 && j != 0 && j != _roomLength - 1) {
                Room[i][j] = new FloorTile(x, y);
            } else if (i == _roomWidth - 1 && j == 0) {
                Room[i][j] = new LeftLowerWallCorner(x,y);
            } else if (i == 0 && j == 0) {
                Room[i][j] = new LeftUpperWallCorner(x,y);
            } else if (i == 0 && j == _roomLength - 1) {
                Room[i][j] = new RightUpperWallCorner(x,y);
            } else if (i == _roomWidth - 1 && j == _roomLength - 1) {
                Room[i][j] = new RightLowerWallCorner(x,y);
            }
        }
    }
}

void room::PutTorchesInRoom() {
    const float TILE_SIZE = 64.f;
    int errorRigthWall = RandomGenerator::getRandomNumber(-1, 1);
    int errorLeftWall = RandomGenerator::getRandomNumber(-1, 1);

    auto placeLeftTorch = [&](int row) {
        if (row >= 0 && row < _roomWidth)
            Room[row][1] = new LeftTorchTile(1 * TILE_SIZE, row * TILE_SIZE);
    };

    auto placeRightTorch = [&](int row) {
        if (row >= 0 && row < _roomWidth)
            Room[row][_roomLength - 2] = new RightTorchTile((_roomLength - 2) * TILE_SIZE, row * TILE_SIZE);
    };

    if (_numberOfTorchersRoom == 1) {
        placeLeftTorch(_roomWidth / 2 + errorLeftWall - 1);
        placeRightTorch(_roomWidth / 2 + errorRigthWall - 1);
    }

    if (_numberOfTorchersRoom == 2) {
        placeLeftTorch(_roomWidth / 3 + errorLeftWall - 1);
        placeLeftTorch(_roomWidth / 3 * 2 + errorLeftWall - 1);
        placeRightTorch(_roomWidth / 3 + errorRigthWall - 1);
        placeRightTorch(_roomWidth / 3 * 2 + errorRigthWall - 1);
    }

    if (_numberOfTorchersRoom == 3) {
        placeLeftTorch(_roomWidth / 2);
        placeLeftTorch(_roomWidth / 4 + errorLeftWall);
        placeLeftTorch(_roomWidth / 4 * 3 + errorLeftWall + 1);
        placeRightTorch(_roomWidth / 2);
        placeRightTorch(_roomWidth / 4 + errorRigthWall);
        placeRightTorch(_roomWidth / 4 * 3 + errorRigthWall + 1);
    }
}

void room::PutColumnsInRoom() {
    int ColumnLength = (_roomLength - 4 - _roomLength  / 4) / (_roomLength / 4 - 1);
    int a = 2 * (_roomWidth / 3) + (_roomWidth % 3) + (_roomWidth % 2) - 1;

    for (int y = 1; y < _roomLength - 2; y += ColumnLength) {
        Room[a][y] = new Column;
        Room[_roomWidth - 1 - a][y] = new Column;
    }
}

RoomBuilder::RoomBuilder() {
    ex = new room();
}

room* RoomBuilder::GetRoom() {
    return ex;
}

void room::draw(sf::RenderWindow& window) {
    for (int i = 0; i < _roomWidth; ++i) {
        for (int j = 0; j < _roomLength; ++j) {
            if (Room[i][j] != nullptr) {
                Room[i][j]->draw(window);
            } else {
                std::cerr << "WARNING: Room[" << i << "][" << j << "] is nullptr!\n";
            }
        }
    }
}

room* Director::CreateRoom(RoomBuilder& builder) {
    builder.SetRoomLength();
    builder.SetRoomWidth();
    builder.SetTorchesInRoom();
    builder.GetRoom()->SetRoom();
    builder.GetRoom()->PutTorchesInRoom();
    return builder.GetRoom();
}
