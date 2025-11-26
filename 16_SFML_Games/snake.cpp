#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;

const int GRID_WIDTH = 30;
const int GRID_HEIGHT = 20;
const int CELL_SIZE=16;
const int WINDOW_WIDTH = CELL_SIZE * GRID_WIDTH;
const int WINDOW_HEIGHT = CELL_SIZE * GRID_HEIGHT;

enum Direction { Down = 0, Left = 1, Right = 2, Up = 3 };
Direction dir = Direction::Right;

int snakeLength=4;

struct Snake 
{ int x,y;}  snakeSegments[100];

struct Fruit
{ int x,y;} fruit;

void updateSnake()
 {
    for (int i= snakeLength;i>0;--i)
    {
        snakeSegments[i].x = snakeSegments[i - 1].x;
        snakeSegments[i].y = snakeSegments[i - 1].y;
    }

    switch (dir)
    {
    case Down:
        snakeSegments[0].y += 1;
        break;
    case Left:
        snakeSegments[0].x -= 1;
        break;
    case Right:
        snakeSegments[0].x += 1;
        break;
    case Up:
        snakeSegments[0].y -= 1;
        break;
    }

    if ((snakeSegments[0].x== fruit.x) && (snakeSegments[0].y== fruit.y))
    {
        snakeLength++;
        fruit.x = rand() % GRID_WIDTH;
        fruit.y = rand() % GRID_HEIGHT;
    }

    if (snakeSegments[0].x > GRID_WIDTH)
    {
        snakeSegments[0].x = 0;
    }
    if (snakeSegments[0].x < 0)
    {
        snakeSegments[0].x = GRID_WIDTH;
    }
    if (snakeSegments[0].y > GRID_HEIGHT)
    {
        snakeSegments[0].y = 0;
    }
    if (snakeSegments[0].y < 0)
    {
       snakeSegments[0].y = GRID_HEIGHT;
    }
 
    for (int i = 1; i < snakeLength; i++)
    {
        if (snakeSegments[0].x == snakeSegments[i].x && snakeSegments[0].y == snakeSegments[i].y)
        {
            snakeLength = i;
        }
    }
 }

int snake()
{  
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");

    Texture tileTexture;
    Texture snakeTexture;
    tileTexture.loadFromFile("images/snake/white.png");
    snakeTexture.loadFromFile("images/snake/red.png");

    Sprite tileSprite(tileTexture);
    Sprite snakeSprite(snakeTexture);

    Clock clock;
    float timer = 0;
    float delay = 0.1;

    fruit.x = 10;
    fruit.y = 10;
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event))
        {
            if (e.type == Event::Closed)
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            dir = Direction::Left;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            dir = Direction::Right;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            dir = Direction::Up;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            dir = Direction::Down;
        }

        if (timer > delay)
        {
            timer = 0; 
            updateSnake();
        }

        ////// draw  ///////
        window.clear();

        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                tileSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
                window.draw(tileSprite);
            }
        }

        for (int i = 0; i < snakeLength; i++)
        {
            snakeSprite.setPosition(snakeSegments[i].x * CELL_SIZE, snakeSegments[i].y * CELL_SIZE);
            window.draw(snakeSprite);
        }
   
        snakeSprite.setPosition(fruit.x * CELL_SIZE, fruit.y * CELL_SIZE);
        window.draw(snakeSprite);

        window.display();
    }

    return 0;
}
