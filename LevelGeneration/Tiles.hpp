#pragma once

#include <iostream>

class Tile {
private:

public:
    Tile() {}

    virtual ~Tile() {}

    virtual void Print() = 0;
};

class FloorTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "f ";
    }

    FloorTile() {}

    ~FloorTile() {}
};

class RightWallTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "rw";
    }

    RightWallTile() {}

    ~RightWallTile() {}
};

class LeftWallTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "lw";
    }

    LeftWallTile() {}

    ~LeftWallTile() {}
};

class UpperWallTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "uw";
    }

    UpperWallTile() {}

    ~UpperWallTile() {}
};

class LowerWallTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "bw";
    }

    LowerWallTile() {}

    ~LowerWallTile() {}
};

class RightTorchTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "rt";
    }

    RightTorchTile() {}

    ~RightTorchTile() {}
};

class LeftTorchTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "lt";
    }

    LeftTorchTile() {}

    ~LeftTorchTile() {}
};

class UpperTorchTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "ut";
    }

    UpperTorchTile() {}

    ~UpperTorchTile() {}
};

class LowerTorchTile : public Tile {
private:

public:
    void Print() override {
        std::cout << "bt";
    }

    LowerTorchTile() {}

    ~LowerTorchTile() {}
};
