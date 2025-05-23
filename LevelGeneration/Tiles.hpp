#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Tile {
protected:
    static constexpr float TILE_SIZE = 64.f;
    sf::Sprite sprite;
    sf::Vector2f position;

public:
    Tile() {}
    virtual ~Tile() {}

    void setPosition(float x, float y) {
        position = {x, y};
        sprite.setPosition(position);
        if (sprite.getTexture()) {
            sprite.setScale(TILE_SIZE / sprite.getTexture()->getSize().x,
                            TILE_SIZE / sprite.getTexture()->getSize().y);
            }
        }

    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
};

class FloorTile : public Tile {
    static sf::Texture texture;
public:
    FloorTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/floor.png"))
        {
            std::cerr << "Ошибка загрузки floor.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

};

class RightWallTile : public Tile {
    static sf::Texture texture;
public:
    RightWallTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/rightWall.png"))
        {
            std::cerr << "Ошибка загрузки rightWall.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

};

class LeftWallTile : public Tile {
    static sf::Texture texture;
public:
    LeftWallTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/leftWall.png"))
        {
            std::cerr << "Ошибка загрузки leftWall.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

};

class UpperWallTile : public Tile {
    static sf::Texture texture;
public:
    UpperWallTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/upperWall.png"))
        {
            std::cerr << "Ошибка загрузки upperWall.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

};

class LowerWallTile : public Tile {
    static sf::Texture texture;
public:
    LowerWallTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/lowerWall.png"))
        {
            std::cerr << "Ошибка загрузки lowerWall.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

};

class RightTorchTile : public Tile {
    static sf::Texture texture;
public:
    RightTorchTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/rightTorch.png"))
        {
            std::cerr << "Ошибка загрузки rightTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

};

class LeftTorchTile : public Tile {
    static sf::Texture texture;
public:
    LeftTorchTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/leftTorch.png"))
        {
            std::cerr << "Ошибка загрузки leftTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

};

class UpperTorchTile : public Tile {
    static sf::Texture texture;
public:
    UpperTorchTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/upperTorch.png"))
        {
            std::cerr << "Ошибка загрузки upperTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

};

class LowerTorchTile : public Tile {
    static sf::Texture texture;
public:
    LowerTorchTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/lowerTorch.png"))
        {
            std::cerr << "Ошибка загрузки lowerTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }
};

class RightUpperWallCorner : public Tile {
private:
    static sf::Texture texture;
public:
    RightUpperWallCorner(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/upperRightCorner.jpg"))
        {
            std::cerr << "Ошибка загрузки lowerTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

    ~RightUpperWallCorner() {}
};

class LeftUpperWallCorner : public Tile {
private:
static sf::Texture texture;
public:
    LeftUpperWallCorner(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/upperLeftCorner.jpg"))
        {
            std::cerr << "Ошибка загрузки lowerTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

    ~LeftUpperWallCorner() {}
};

class RightLowerWallCorner : public Tile {
private:
static sf::Texture texture;
public:
    RightLowerWallCorner(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/lowerRightCorner.jpg"))
        {
            std::cerr << "Ошибка загрузки lowerTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

    ~RightLowerWallCorner() {}
};

class LeftLowerWallCorner : public Tile {
private:
static sf::Texture texture;
public:
    LeftLowerWallCorner(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/lowerLeftCorner.jpg"))
        {
            std::cerr << "Ошибка загрузки lowerTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

    ~LeftLowerWallCorner() {}
};

class ColumnTile : public Tile {
private:
static sf::Texture texture;
public:
    ColumnTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/column.png"))
        {
            std::cerr << "Ошибка загрузки lowerTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

    ~ColumnTile() {}
};

class WaterTile : public Tile {
private:
static sf::Texture texture;
public:
    WaterTile(float x = 0.f, float y = 0.f) {
        if (texture.getSize().x == 0 &&
            !texture.loadFromFile("assets/pictures/tiles/water.png"))
        {
            std::cerr << "Ошибка загрузки lowerTorch.png\n";
        }
        sprite.setTexture(texture);
        sprite.setScale(TILE_SIZE / texture.getSize().x, TILE_SIZE / texture.getSize().y);
        setPosition(x, y);
    }

    ~WaterTile() {}
};
