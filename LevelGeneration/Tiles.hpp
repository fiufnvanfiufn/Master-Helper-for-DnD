#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile {
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position;

public:
    Tile() {}
    virtual ~Tile() {}

    virtual void Print() = 0;

    void setPosition(float x, float y) {
        position = {x, y};
        sprite.setPosition(position);
    }

    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

class FloorTile : public Tile {
public:
    FloorTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/floor.png")) {
            std::cerr << "Ошибка загрузки floor.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "f ";
    }

    ~FloorTile() {}
};

class RightWallTile : public Tile {
public:
    RightWallTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/right_wall.png")) {
            std::cerr << "Ошибка загрузки right_wall.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "rw";
    }

    ~RightWallTile() {}
};

class LeftWallTile : public Tile {
public:
    LeftWallTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/left_wall.png")) {
            std::cerr << "Ошибка загрузки left_wall.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "lw";
    }

    ~LeftWallTile() {}
};

class UpperWallTile : public Tile {
public:
    UpperWallTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/upper_wall.png")) {
            std::cerr << "Ошибка загрузки upper_wall.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "uw";
    }

    ~UpperWallTile() {}
};

class LowerWallTile : public Tile {
public:
    LowerWallTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/lower_wall.png")) {
            std::cerr << "Ошибка загрузки lower_wall.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "bw";
    }

    ~LowerWallTile() {}
};

class RightTorchTile : public Tile {
public:
    RightTorchTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/right_torch.png")) {
            std::cerr << "Ошибка загрузки right_torch.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "rt";
    }

    ~RightTorchTile() {}
};

class LeftTorchTile : public Tile {
public:
    LeftTorchTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/left_torch.png")) {
            std::cerr << "Ошибка загрузки left_torch.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "lt";
    }

    ~LeftTorchTile() {}
};

class UpperTorchTile : public Tile {
public:
    UpperTorchTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/upper_torch.png")) {
            std::cerr << "Ошибка загрузки upper_torch.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "ut";
    }

    ~UpperTorchTile() {}
};

class LowerTorchTile : public Tile {
public:
    LowerTorchTile(float x = 0.f, float y = 0.f) {
        if (!texture.loadFromFile("assets/pictures/tiles/lower_torch.png")) {
            std::cerr << "Ошибка загрузки lower_torch.png\n";
        }
        sprite.setTexture(texture);
        setPosition(x, y);
    }

    void Print() override {
        std::cout << "bt";
    }

    ~LowerTorchTile() {}
};
