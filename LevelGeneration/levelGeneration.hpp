#pragma once

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
    int _roomLength;
    int _roomWidth;
    char** Room;
public:
    room() {
        Room = new char*[_roomWidth];
        for (int i{}; i < _roomWidth; ++i) {
            Room[i] = new char[_roomLength];
        }
    }

    ~room() {
        for (int i{}; i < _roomWidth; ++i) {
            delete[] Room[i];
        }
        delete[] Room;
    }

    void SetRoomWidth(int roomWidth) {
        _roomWidth = roomWidth;
    }

    void SetRoomLength(int roomLength) {
        _roomLength = roomLength;
    }

    void SetRoom() {
        if (Room != nullptr) {
            for (int i{}; i < _roomWidth; ++i) {
                delete[] Room[i];
            }
            delete[] Room;
        }


        Room = new char*[_roomWidth];
        for (int i{}; i < _roomWidth; ++i) {
            Room[i] = new char[_roomLength];
        }

        for (int i{}; i < _roomWidth; ++i) {
            for (int j{}; j < _roomLength; ++j)
                if (i == _roomWidth - 1 || i == 0 || j == 0 || j == _roomLength - 1) {
                    Room[i][j] = 's';
                } else {
                    Room[i][j] = 'f';
                }
        }
    }

    void print() {
        for (int i{}; i < _roomWidth; ++i) {
            for (int j{}; j < _roomLength; ++j)
                std::cout << '[' << Room[i][j] << ']' << std::endl;
        }
        std::cout << std::endl;
    }
};


class RoomBuilder {
protected:
    room* ex;
public:
    RoomBuilder() {
        ex = new room();
    }
    virtual ~RoomBuilder() {
        delete ex;
    }
    virtual void setRoomLength() = 0;
    virtual void setRoomWidth() = 0;

    room* GetRoom() {
        return ex;
    }
};

class SmallRoomBuilder: public RoomBuilder {
public:
    void setRoomLength() override {
        ex->SetRoomLength(RandomGenerator::getRandomNumber(4, 7));
    }

    void setRoomWidth() override {
        ex->SetRoomWidth(RandomGenerator::getRandomNumber(4, 8));
    }
};

class LargeRoomBuilder: public RoomBuilder {
public:
    void setRoomLength() override {
        ex->SetRoomLength(RandomGenerator::getRandomNumber(8, 12));
        ex->SetRoom();
    }

    void setRoomWidth() override {
        ex->SetRoomWidth(RandomGenerator::getRandomNumber(10, 14));
        ex->SetRoom();
    }
};

class Director {
public:
    room* CreateRoom(RoomBuilder& builder) {
        builder.setRoomLength();
        builder.setRoomWidth();
        return builder.GetRoom();
    }
};
