#pragma once

#include "Tiles.hpp"
#include <iostream>
#include <random>
#include <vector>

class RandomGenerator {
public:
    int operator()(int min, int max) {
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
    int _waterRadius = 0;

    std::vector<std::vector<Tile*>> Room;

    bool IsColumnsInRoom = false;
    bool IsTorchesInRoom = false;
    bool IsWaterInRoom = false;
public:
    room() {}

    ~room();

    void draw(sf::RenderWindow& window);

    void SetRoomWidth(int roomWidth);

    void SetRoomLength(int roomLength);

    void SetNumberOfTorchesInRoom(int numberOfTorchersRoom);

    void SetWaterRadius(int waterRadius);

    void SetRoom();

    void PutTorchesInRoom();

    void PutColumnsInRoom();

    void PutWaterInRoom();
};

class RoomBuilder {
protected:
    room* ex;
    RandomGenerator Generator;
public:
    RoomBuilder();

    virtual ~RoomBuilder() {
        // delete ex;
    }

    virtual void SetRoomLength() = 0;
    virtual void SetRoomWidth() = 0;
    virtual void SetTorchesInRoom() = 0;
    virtual void SetColumnsInRoom() = 0;
    virtual void SetWaterInRoom() = 0;

    room* GetRoom();
};

class SmallRoomBuilder : public RoomBuilder {
public:
    void SetRoomLength() override {
        ex->SetRoomLength(Generator(8, 10));
    }

    void SetRoomWidth() override {
        ex->SetRoomWidth(Generator(8, 10));
    }

    void SetTorchesInRoom() override {
        ex->SetNumberOfTorchesInRoom(1);
    }

    void SetWaterInRoom() override {
        ex->SetWaterRadius(1);
    }

    void SetColumnsInRoom() override {
        ex->PutColumnsInRoom();
    }
};

class LargeRoomBuilder : public RoomBuilder {
public:
    void SetRoomLength() override {
        ex->SetRoomLength(Generator(12, 18));
    }

    void SetRoomWidth() override {
        ex->SetRoomWidth(Generator(14, 16));
    }

    void SetTorchesInRoom() override {
        ex->SetNumberOfTorchesInRoom(3);
    }

    void SetWaterInRoom() override {
        ex->SetWaterRadius(2);
    }

    void SetColumnsInRoom() override {
        ex->PutColumnsInRoom();
    }
};

class Director {
public:
    room* CreateRoom(RoomBuilder& builder);
};
