#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
using namespace std;

float deltaTime = 0;
Clock gameclock;

float timer = 0.0f;
float delay = 0.5f;

Vector2f velocity = { 0,0 };

int score = 0;
int lives = 3;

int level = 1;


int board[19][19] =
{
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0},
  {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int main()
{
    srand(time(0));
    int randomNumber = rand() % 10;
    int i = 0;
    int score = 0;


    CircleShape point((4.0f));
    point.setFillColor(Color::Yellow);

    RectangleShape pathp(Vector2f(40.0f, 40.0f));
    pathp.setFillColor(Color::Blue);

    RectangleShape wall(Vector2f(40.0f, 40.0f));
    wall.setFillColor(Color::Black);

    RectangleShape path(Vector2f(40.0f, 40.0f));
    path.setFillColor(Color::Blue);

    Texture strawberrytexture;
    strawberrytexture.loadFromFile("./pics/strawberry.png");
    Sprite strawberry;
    strawberry.setTexture(strawberrytexture);
    strawberry.setScale(0.05, 0.05);
    strawberry.setPosition(50, 50);

    Texture cherrytexture;
    cherrytexture.loadFromFile("./pics/cherry.png");
    Sprite cherry;
    cherry.setTexture(cherrytexture);
    cherry.setScale(0.05, 0.05);
    cherry.setPosition(80, 60);

    Texture cointexture;
    cointexture.loadFromFile("./pics/coin.png");
    Sprite coin;
    coin.setTexture(cointexture);
    coin.setScale(0.03, 0.03);

    

    Texture Pactexture;
    Pactexture.loadFromFile("./pics/pacman2.PNG");
    Sprite Pacsprite(Pactexture);
    Pacsprite.setTextureRect(IntRect(0, 0, 65, 64));
    Pacsprite.setPosition(Vector2f(50.0f, 50.0f));
    Pacsprite.setOrigin(Pacsprite.getTextureRect().width / 2, Pacsprite.getTextureRect().height / 2);
    Vector2i Pacsprite_position(0, 0);

    RenderWindow window(VideoMode(800, 800), "Pacman");
    while (window.isOpen())
    {


        //if (score >= 50)
        //{
        //    // play sound effect
        //    level++;
        //    // change color or texture for level i

        //    score = score % 50;
       // }
        //if (score >= 50)
        //{
        //    // play sound effect
        //    // change color or texture for level 3
        //    level2 = false;
        //    level3 = true;
        //}
        //if (score >= 50)
        //{
        //    // play sound effect
        //    // change color or texture for level 4
        //    level3 = false;
        //    level4 = true;
        //}

        deltaTime = gameclock.getElapsedTime().asSeconds();
        float speed = 0.18;

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();

        window.draw(strawberry);
        window.draw(cherry);
        window.draw(coin);

        for (int i = 0; i < 19; i++)
        {
            for (int j = 0; j < 19; j++)
            {
                if (board[i][j] == 0)
                {
                    wall.setPosition(i * 40.0f + (800 - 19 * 40.0f) / 2, j * 40.0f + (800 - 19 * 40.0f) / 2);
                    window.draw(wall);
                    //if (pacman.getGlobalBounds().intersects(wall.getGlobalBounds()))
                    //{
                    //    //////////////////////////////////////////////////////
                    //}


                }
                else if (board[i][j] == 1)
                {
                    point.setPosition(i * 40.0f + (800 - 19 * 40.0f) / 2 + 13.0f, j * 40.0f + (800 - 19 * 40.0f) / 2 + 13.0f);
                    pathp.setPosition(i * 40.0f + (800 - 19 * 40.0f) / 2, j * 40.0f + (800 - 19 * 40.0f) / 2);
                    if (Pacsprite.getGlobalBounds().intersects(point.getGlobalBounds()))
                    {
                        point.setFillColor(Color::Blue);
                        board[i][j] = 2; // Update the board to mark the point as eaten
                        score += 2;
                    }
                    else
                    {
                        point.setFillColor(Color::Yellow);
                    }

                    window.draw(pathp);
                    window.draw(point);
                }
                else if (board[i][j] == 2)
                {
                    // Render eaten points in blue
                    path.setPosition(i * 40.0f + (800 - 19 * 40.0f) / 2, j * 40.0f + (800 - 19 * 40.0f) / 2);
                    window.draw(path);
                }
            }
        }
       

        Pacsprite_position.x = (Pacsprite.getPosition().x) / 40;
        Pacsprite_position.y = (Pacsprite.getPosition().y) / 40;
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if (board[Pacsprite_position.x][Pacsprite_position.y - 1] != 0)
            {
                velocity.x = 0;
                if (timer < 0)
                {
                    //Pacsprite.setScale(1, -1);
                    i++;
                    i = i % 2;
                    Pacsprite.setTextureRect(IntRect((i * 65), 192, 65, 64));
                    velocity.y = -speed;
                    timer = delay;
                }
                else
                    timer -= deltaTime;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if (board[Pacsprite_position.x][Pacsprite_position.y] != 0)

            {
                velocity.x = 0;
                if (timer < 0)
                {
                    //Pacsprite.setScale(1, 1);
                    i++;
                    i = i % 2;
                    Pacsprite.setTextureRect(IntRect((i * 65), 64, 65, 64));
                    velocity.y = speed;
                    timer = delay;
                }
                else
                    timer -= deltaTime;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if (board[Pacsprite_position.x - 1][Pacsprite_position.y] != 0)

            {
                velocity.y = 0;
                if (timer < 0)
                {
                    //Pacsprite.setScale(-1, 1);
                    i++;
                    i = i % 2;
                    Pacsprite.setTextureRect(IntRect((i * 65), 128, 65, 64));
                    velocity.x = -speed;
                    timer = delay;
                }
                else
                    timer -= deltaTime;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            if (board[Pacsprite_position.x][Pacsprite_position.y] != 0)
            {
                velocity.y = 0;
                if (timer < 0)
                {
                    //Pacsprite.setScale(1, 1);
                    i++;
                    i = i % 2;
                    Pacsprite.setTextureRect(IntRect((i * 65), 0, 65, 64));
                    velocity.x = speed;
                    timer = delay;
                }
                else
                    timer -= deltaTime;
            }
        }
        else
        {
            velocity.x = 0;
            velocity.y = 0;
        }
        Pacsprite.move(velocity);

        window.draw(Pacsprite);
        window.draw(strawberry);
        window.draw(cherry);
        window.draw(coin);
        window.display();
        window.clear();


    }

    return 0;
}