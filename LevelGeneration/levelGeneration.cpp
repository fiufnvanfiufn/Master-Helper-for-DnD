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
sf::Texture ColumnTile::texture;
sf::Texture WaterTile::texture;

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

void room::SetNumberOfTorchesInRoom(int numberOfTorchersRoom) {
    _numberOfTorchersRoom = numberOfTorchersRoom;
}

void room::SetWaterRadius(int waterRadius) {
    _waterRadius = waterRadius;
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
            if (Room[i][j] != nullptr) {
                    delete Room[i][j];
            }
            if (i == _roomWidth - 1 && j != 0 && j != _roomLength - 1) {
                Room[i][j] = new LowerWallTile(x, y);
            } else if(i == 0 && j != 0 && j != _roomLength - 1) {
                Room[i][j] = new UpperWallTile(x, y);
            } else if(j == _roomLength - 1 && i != 0 && i != _roomWidth - 1) {
                Room[i][j] = new RightWallTile(x, y);
            } else if (j == 0 && i != 0 && i != _roomWidth - 1){
                Room[i][j] = new LeftWallTile(x, y);
            }  else if (i == _roomWidth - 1 && j == 0) {
                Room[i][j] = new LeftLowerWallCorner(x,y);
            } else if (i == 0 && j == 0) {
                Room[i][j] = new LeftUpperWallCorner(x,y);
            } else if (i == 0 && j == _roomLength - 1) {
                Room[i][j] = new RightUpperWallCorner(x,y);
            } else if (i == _roomWidth - 1 && j == _roomLength - 1) {
                Room[i][j] = new RightLowerWallCorner(x,y);
            } else {
                Room[i][j] = new FloorTile(x, y);
            }
        }
    }
}

void room::PutTorchesInRoom() {
    const float TILE_SIZE = 64.f;
    RandomGenerator Generator;
    int errorRigthWall = Generator(-1, 1);
    int errorLeftWall = Generator(-1, 1);

    auto placeLeftTorch = [&](int row) {
        if (row >= 0 && row < _roomWidth)
            Room[row][1] = new LeftTorchTile(1 * TILE_SIZE, row * TILE_SIZE);
    };

    auto placeRightTorch = [&](int row) {
        if (row >= 0 && row < _roomWidth)
            Room[row][_roomLength - 2] = new RightTorchTile((_roomLength - 2) * TILE_SIZE, row * TILE_SIZE);
    };
    if (_numberOfTorchersRoom == 0) {
        return;
    }

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
    const float TILE_SIZE = 64.f;
    int MARGIN{};
    const int WALL_THICKNESS = 1;
    int margin = (_roomLength % 2 == 0) ? 1 : 2;

    int availableSpace = _roomLength - 2 * WALL_THICKNESS - 2 * margin;

    int columnCount = (_roomLength % 2 == 0) ? 3 : 2;

    int columnSpacing = (availableSpace > 0) ? availableSpace / (columnCount + 1) : 0;

    int column1Pos = _roomWidth / 3;
    int column2Pos = _roomWidth - 1 - column1Pos;

    for (int y = margin + WALL_THICKNESS;
         y < _roomLength - margin - WALL_THICKNESS;
         y += columnSpacing + 1) {

        float xPos1 = y * TILE_SIZE;
        float yPos1 = column1Pos * TILE_SIZE;
        float xPos2 = y * TILE_SIZE;
        float yPos2 = column2Pos * TILE_SIZE;

        if (Room[column1Pos][y]) delete Room[column1Pos][y];
        if (Room[column2Pos][y]) delete Room[column2Pos][y];

        Room[column1Pos][y] = new ColumnTile(xPos1, yPos1);
        Room[column2Pos][y] = new ColumnTile(xPos2, yPos2);

        if (columnSpacing <= 0) break;
    }
}

void room::PutWaterInRoom() {
    const float TILE_SIZE = 64.f;
    RandomGenerator Generator;

    if (_waterRadius == 1) {
        int i = Generator(3, _roomWidth - 3);
        int j = Generator(3, _roomLength - 3);

        delete Room[i][j];
        delete Room[i + 1][j];
        delete Room[i - 1][j];
        delete Room[i][j + 1];
        delete Room[i][j - 1];

        Room[i][j]         = new WaterTile(j * TILE_SIZE, i * TILE_SIZE);
        Room[i + 1][j]     = new WaterTile(j * TILE_SIZE, (i + 1) * TILE_SIZE);
        Room[i - 1][j]     = new WaterTile(j * TILE_SIZE, (i - 1) * TILE_SIZE);
        Room[i][j + 1]     = new WaterTile((j + 1) * TILE_SIZE, i * TILE_SIZE);
        Room[i][j - 1]     = new WaterTile((j - 1) * TILE_SIZE, i * TILE_SIZE);

    }else if (_waterRadius == 2) {
        int x = Generator(2, _roomWidth - 7);
        int y = Generator(2, _roomLength - 7);
        for (int i = x; i < x + 5; ++i) {
            for (int j = y; j < y + 5; ++j) {
                if ((i != x || j != y + 4) && (i != x || j != y) && (i != x + 4 || j != y + 4) &&
                    (i != x + 4 || j != y)) {
                    delete Room[i][j];
                    Room[i][j] = new WaterTile(j * TILE_SIZE, i * TILE_SIZE);
                }
            }
        }
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
    builder.SetWaterInRoom();
    builder.GetRoom()->SetRoom();
    return builder.GetRoom();
}
