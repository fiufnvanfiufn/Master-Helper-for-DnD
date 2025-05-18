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
    const int WALL_THICKNESS = 1;  // Толщина стены в клетках
    // Определяем отступ в зависимости от четности длины комнаты
    int margin = (_roomLength % 2 == 0) ? 1 : 2;  // 1 для четных, 2 для нечетных

    // Рассчитываем доступное пространство для колонн
    int availableSpace = _roomLength - 2 * WALL_THICKNESS - 2 * margin;

    // Количество колонн в ряду (минимум 2)
    int columnCount = 2;

    // Рассчитываем расстояние между колоннами
    int columnSpacing = (availableSpace > 0) ? availableSpace / (columnCount + 1) : 0;

    // Позиции колонн по ширине (1/3 и 2/3 ширины комнаты)
    int column1Pos = _roomWidth / 3;
    int column2Pos = _roomWidth - 1 - column1Pos;

    // Расставляем колонны
    for (int y = margin + WALL_THICKNESS;
         y < _roomLength - margin - WALL_THICKNESS;
         y += columnSpacing + 1) {

        float xPos1 = y * TILE_SIZE;
        float yPos1 = column1Pos * TILE_SIZE;
        float xPos2 = y * TILE_SIZE;
        float yPos2 = column2Pos * TILE_SIZE;

        // Очищаем старые тайлы
        if (Room[column1Pos][y]) delete Room[column1Pos][y];
        if (Room[column2Pos][y]) delete Room[column2Pos][y];

        // Создаем новые колонны
        Room[column1Pos][y] = new ColumnTile(xPos1, yPos1);
        Room[column2Pos][y] = new ColumnTile(xPos2, yPos2);

        // Защита от бесконечного цикла
        if (columnSpacing <= 0) break;
    }
}

void room::PutWaterInRoom() {
    int i = RandomGenerator::getRandomNumber(3, _roomWidth - 2);
    int j = RandomGenerator::getRandomNumber(3, _roomLength - 2);

    const float TILE_SIZE = 64.f;

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

room* Director::CreateRoom(RoomBuilder& builder, bool IsTorchesInRoom, bool IsColumnInRoom, bool IsWaterInRoom) {
    builder.SetRoomLength();
    builder.SetRoomWidth();
    builder.SetTorchesInRoom(IsTorchesInRoom);
    builder.GetRoom()->SetRoom();
    return builder.GetRoom();
}
