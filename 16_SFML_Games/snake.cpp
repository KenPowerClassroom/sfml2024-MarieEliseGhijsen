#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

const int N = 30;
const int M = 20;
const int sz=16;
const int w = sz*N;
const int h = sz*M;

enum Direction { Down = 0, Left = 1, Right = 2, Up = 3 };
Direction dir = Direction::Right;

int num=4;

struct Snake 
{ int x,y;}  s[100];

struct Fruit
{ int x,y;} f;

void Tick()
 {
    for (int i=num;i>0;--i)
     {s[i].x=s[i-1].x; s[i].y=s[i-1].y;}

    if (dir== Direction::Down) s[0].y+=1;
    if (dir== Direction::Left) s[0].x-=1;
    if (dir== Direction::Right) s[0].x+=1;
    if (dir== Direction::Up) s[0].y-=1;

    if ((s[0].x==f.x) && (s[0].y==f.y)) 
     {num++; f.x=rand()%N; f.y=rand()%M;}

    if (s[0].x>N) s[0].x=0;  if (s[0].x<0) s[0].x=N;
    if (s[0].y>M) s[0].y=0;  if (s[0].y<0) s[0].y=M;
 
    for (int i=1;i<num;i++)
     if (s[0].x==s[i].x && s[0].y==s[i].y)  num=i;
 }

int snake()
{  
    srand(time(0));

    RenderWindow window(VideoMode(w, h), "Snake Game!");

    Texture t1,t2;
    t1.loadFromFile("images/snake/white.png");
    t2.loadFromFile("images/snake/red.png");

    Sprite sprite1(t1);
    Sprite sprite2(t2);

    Clock clock;
    float timer=0, delay=0.1;

    f.x=10;
    f.y=10; 
    
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

        if (timer>delay) {timer=0; Tick();}

   ////// draw  ///////
    window.clear();

    for (int i=0; i<N; i++) 
      for (int j=0; j<M; j++) 
        { sprite1.setPosition(i*sz, j*sz);  window.draw(sprite1); }

    for (int i=0;i<num;i++)
        { sprite2.setPosition(s[i].x*sz, s[i].y*sz);  window.draw(sprite2); }
   
    sprite2.setPosition(f.x*sz, f.y*sz);  window.draw(sprite2);    

    window.display();
    }

    return 0;
}
