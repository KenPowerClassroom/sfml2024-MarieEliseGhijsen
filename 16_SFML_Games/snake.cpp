#include <SFML/Graphics.hpp>
#include <time.h>
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
        snakeSegments[i].x= snakeSegments[i-1].x; snakeSegments[i].y= snakeSegments[i-1].y;}

    if (dir== Direction::Down) snakeSegments[0].y+=1;
    if (dir== Direction::Left) snakeSegments[0].x-=1;
    if (dir== Direction::Right) snakeSegments[0].x+=1;
    if (dir== Direction::Up) snakeSegments[0].y-=1;

    if ((snakeSegments[0].x== fruit.x) && (snakeSegments[0].y== fruit.y))
     {
        snakeLength++; fruit.x=rand()% GRID_WIDTH; fruit.y=rand()% GRID_HEIGHT;}

    if (snakeSegments[0].x> GRID_WIDTH) snakeSegments[0].x=0;  if (snakeSegments[0].x<0) snakeSegments[0].x= GRID_WIDTH;
    if (snakeSegments[0].y> GRID_HEIGHT) snakeSegments[0].y=0;  if (snakeSegments[0].y<0) snakeSegments[0].y= GRID_HEIGHT;
 
    for (int i=1;i< snakeLength;i++)
     if (snakeSegments[0].x== snakeSegments[i].x && snakeSegments[0].y== snakeSegments[i].y)  snakeLength =i;
 }

int snake()
{  
    srand(time(0));

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game!");

    Texture t1,t2;
    t1.loadFromFile("images/snake/white.png");
    t2.loadFromFile("images/snake/red.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer=0, delay=0.1;

    fruit.x=10;
    fruit.y=10;
    
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time; 

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)      
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) dir = Direction::Left;
        if (Keyboard::isKeyPressed(Keyboard::Right)) dir = Direction::Right;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir = Direction::Up;
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir = Direction::Down;

        if (timer>delay) {timer=0; updateSnake();}

   ////// draw  ///////
    window.clear();

    for (int i=0; i< GRID_WIDTH; i++)
      for (int j=0; j< GRID_HEIGHT; j++)
        { sprite1.setPosition(i* CELL_SIZE, j* CELL_SIZE);  window.draw(sprite1); }

    for (int i=0;i< snakeLength;i++)
        { sprite2.setPosition(snakeSegments[i].x* CELL_SIZE, snakeSegments[i].y* CELL_SIZE);  window.draw(sprite2); }
   
    sprite2.setPosition(fruit.x* CELL_SIZE, fruit.y* CELL_SIZE);  window.draw(sprite2);

    window.display();
    }

    return 0;
}
