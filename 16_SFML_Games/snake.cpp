#include "SnakeGame.h"

SnakeGame::SnakeGame() : direction(Right), snakeLegnth(4), timer(0.0f), delay(0.0f)
{
    for (int i = 0; i < MAX_SNAKE_LENGTH; i++)
    {
        segments[i] = { 0,0 };
    }

    fruit = { 10, 10 };

    tileTexture.loadFromFile("images/snake/white.png");
    snakeTexture.loadFromFile("images/snake/red.png");

    tileSprite.setTexture(tileTexture);
    snakeSprite.setTexture(snakeTexture);
}

void SnakeGame::runGame()
{
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");

    Clock clock;
    float timer = 0;
    float delay = 0.1;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            direction = Direction::Left;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            direction = Direction::Right;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            direction = Direction::Up;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            direction = Direction::Down;
        }

        if (timer > delay)
        {
            timer = 0;
            update();
        }

        ////// draw  ///////
        window.clear();
        draw(window);
        window.display();
    }
}

void SnakeGame::update()
 {
    for (int i= snakeLegnth;i>0;--i)
    {
        segments[i].x = segments[i - 1].x;
        segments[i].y = segments[i - 1].y;
    }

    switch (direction)
    {
    case Down:
        segments[0].y += 1;
        break;
    case Left:
        segments[0].x -= 1;
        break;
    case Right:
        segments[0].x += 1;
        break;
    case Up:
        segments[0].y -= 1;
        break;
    }

    if ((segments[0].x== fruit.x) && (segments[0].y== fruit.y))
    {
        snakeLegnth++;
        fruit.x = rand() % GRID_WIDTH;
        fruit.y = rand() % GRID_HEIGHT;
    }

    if (segments[0].x > GRID_WIDTH)
    {
        segments[0].x = 0;
    }
    if (segments[0].x < 0)
    {
        segments[0].x = GRID_WIDTH - 1;
    }
    if (segments[0].y > GRID_HEIGHT)
    {
        segments[0].y = 0;
    }
    if (segments[0].y < 0)
    {
        segments[0].y = GRID_HEIGHT - 1;
    }
 
    for (int i = 1; i < snakeLegnth; i++)
    {
        if (segments[0].x == segments[i].x && segments[0].y == segments[i].y)
        {
            snakeLegnth = i;
        }
    }
 }

void SnakeGame::draw(RenderWindow& t_window)
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        for (int j = 0; j < GRID_HEIGHT; j++)
        {
            tileSprite.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            t_window.draw(tileSprite);
        }
    }

    for (int i = 0; i < snakeLegnth; i++)
    {
        snakeSprite.setPosition(segments[i].x * CELL_SIZE, segments[i].y * CELL_SIZE);
        t_window.draw(snakeSprite);
    }

    snakeSprite.setPosition(fruit.x * CELL_SIZE, fruit.y * CELL_SIZE);
    t_window.draw(snakeSprite);
}