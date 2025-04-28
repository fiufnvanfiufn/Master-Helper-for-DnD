#pragma once

#include "Tiles.hpp"
#include <iostream>
#include <random>

class RandomGenerator {
public:
    static int getRandomNumber(int min, int max) {
        static std::random_device rd;
        static std::mt19937 generator(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(generator);
    }
};

class room {
private:
    int _roomLength = 0;
    int _roomWidth = 0;
    int _numberOfTorchersRoom = 0;
    Tile*** Room = nullptr;

    FloorTile floorTile;
    RightWallTile rightWallTile;
    LeftWallTile leftWallTile;
    UpperWallTile upperWallTile;
    LowerWallTile lowerWallTile;
    LeftTorchTile leftTorchTile;
    RightTorchTile rightTorchTile;
public:
    room() {}

    ~room();

    void SetRoomWidth(int roomWidth);

    void SetRoomLength(int roomLength);

    void SetTorchesInRoom(int numberOfTorchersRoom);

    void SetRoom();

    void PutTorchesInRoom();

    void print();
};

class RoomBuilder {
protected:
    room* ex;
public:
    RoomBuilder();

    virtual ~RoomBuilder() {
        delete ex;
    }

    virtual void SetRoomLength() = 0;
    virtual void SetRoomWidth() = 0;
    virtual void SetTorchesInRoom() = 0;

    room* GetRoom();
};

class SmallRoomBuilder : public RoomBuilder {
public:
    void SetRoomLength() override {
        ex->SetRoomLength(RandomGenerator::getRandomNumber(4, 7));
    }

    void SetRoomWidth() override {
        ex->SetRoomWidth(RandomGenerator::getRandomNumber(5, 8));
    }

    void SetTorchesInRoom() override {
        ex->SetTorchesInRoom(1);
    }
};

class LargeRoomBuilder : public RoomBuilder {
public:
    void SetRoomLength() override {
        ex->SetRoomLength(RandomGenerator::getRandomNumber(8, 12));
    }

    void SetRoomWidth() override {
        ex->SetRoomWidth(RandomGenerator::getRandomNumber(10, 14));
    }

    void SetTorchesInRoom() override {
        ex->SetTorchesInRoom(3);
    }
};

class Director {
public:
    room* CreateRoom(RoomBuilder& builder);
};
