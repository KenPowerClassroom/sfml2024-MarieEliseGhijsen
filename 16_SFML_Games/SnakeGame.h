#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;

class SnakeGame
{
public:
    static const int GRID_WIDTH = 30;
    static const int GRID_HEIGHT = 20;
    static const int CELL_SIZE = 16;
    static const int WINDOW_WIDTH = CELL_SIZE * GRID_WIDTH;
    static const int WINDOW_HEIGHT = CELL_SIZE * GRID_HEIGHT;
    static const int MAX_SNAKE_LENGTH = 100;

    enum Direction { Down = 0, Left = 1, Right = 2, Up = 3 };

    SnakeGame();

    void runGame();

private:
    struct snakeSegment { int x, y; };
    snakeSegment segments[100];
    snakeSegment fruit;

    Direction direction;
    int snakeLegnth;

    Texture tileTexture;
    Texture snakeTexture;

    Sprite tileSprite;
    Sprite snakeSprite;

    float timer;
    float delay;

    void update();
    void draw(RenderWindow& t_window);
};