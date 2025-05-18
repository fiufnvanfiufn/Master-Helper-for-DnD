#pragma once

#include "Tiles.hpp"
#include <iostream>
#include <random>
#include <vector>

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

    void SetTorchesInRoom(int numberOfTorchersRoom);

    void SetRoom();

    void PutTorchesInRoom();

    void PutColumnsInRoom();

    void PutWaterInRoom();
};

class RoomBuilder {
protected:
    room* ex;
public:
    RoomBuilder();

    virtual ~RoomBuilder() {
        // delete ex;
    }

    virtual void SetRoomLength() = 0;
    virtual void SetRoomWidth() = 0;
    virtual void SetTorchesInRoom(bool IsTorchesInRoom) = 0;
    virtual void SetColumnsInRoom(bool IsColumnInRoom) = 0;
    virtual void SetWaterInRoom(bool IsWaterInRoom) = 0;

    room* GetRoom();
};

class SmallRoomBuilder : public RoomBuilder {
public:
    void SetRoomLength() override {
        ex->SetRoomLength(RandomGenerator::getRandomNumber(8, 10));
    }

    void SetRoomWidth() override {
        ex->SetRoomWidth(RandomGenerator::getRandomNumber(8, 10));
    }

    void SetTorchesInRoom(bool IsTorchesInRoom) override {
        if (IsTorchesInRoom) {
            ex->SetTorchesInRoom(1);
        }

    }

    void SetWaterInRoom(bool IsWaterInRoom) override {
        if (IsWaterInRoom) {
            ex->PutWaterInRoom();
        }

    }

    void SetColumnsInRoom(bool IsColumnInRoom) override {
        if (IsColumnInRoom) {
            ex->PutColumnsInRoom();
        }

    }
};

class LargeRoomBuilder : public RoomBuilder {
public:
    void SetRoomLength() override {
        ex->SetRoomLength(RandomGenerator::getRandomNumber(12, 18));
    }

    void SetRoomWidth() override {
        ex->SetRoomWidth(RandomGenerator::getRandomNumber(14, 20));
    }

    void SetTorchesInRoom(bool IsTorchesInRoom) override {
        if (IsTorchesInRoom) {
            ex->SetTorchesInRoom(3);
        }

    }

    void SetWaterInRoom(bool IsWaterInRoom) override {
        if (IsWaterInRoom) {
            ex->PutWaterInRoom();
        }

    }

    void SetColumnsInRoom(bool IsColumnInRoom) override {
        if (IsColumnInRoom) {
            ex->PutColumnsInRoom();
        }

    }
};

class Director {
public:
    room* CreateRoom(RoomBuilder& builder, bool IsTorchesInRoom = false, bool IsColumnInRoom = false, bool IsWaterInRoom = false);
};
