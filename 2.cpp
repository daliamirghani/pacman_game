#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
using namespace sf;
using namespace std;

float deltaTime = 0;
Clock gameclock;

float timer = 0.0f;
float delay = 0.5f;

bool straw_eaten = false;
bool cherry_eaten = false;
bool coin_eaten = false;
bool coin2_eaten = false;
bool coin3_eaten = false;
bool coin4_eaten = false;

bool ghost1_eaten = false;
bool ghost2_eaten = false;
bool ghost3_eaten = false;
bool ghost4_eaten = false;

int score = 000;
int lives = 3;
int level = 1;
bool level2 = false;
bool level3 = false;
bool level4 = false;
bool level5 = false;

//void resetGhostPosition(Sprite& ghost)
//{
//    float x = rand() % 600;
//    float y = rand() % 600;
//    ghost.setPosition(x, y);
//}


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

    srand(time(nullptr));
    float y1 = rand() % 600, x1 = rand() % 600;
    float y2 = rand() % 600, x2 = rand() % 600;
    float y3 = rand() % 600, x3 = rand() % 600;
    float y4 = rand() % 600, x4 = rand() % 600;

    int i = 0;

    CircleShape point((4.0f));
    point.setFillColor(Color::Yellow);

    RectangleShape pathp(Vector2f(50.0f, 50.0f));
    pathp.setFillColor(Color::Blue);

    RectangleShape wall(Vector2f(40.0f, 40.0f));
    wall.setFillColor(Color::Black);

    RectangleShape path(Vector2f(40.0f, 40.0f));
    path.setFillColor(Color::Blue);

    Texture strawberrytexture;
    strawberrytexture.loadFromFile("strawberry.png");
    Sprite strawberry;
    strawberry.setTexture(strawberrytexture);
    strawberry.setScale(0.06, 0.06);
    strawberry.setPosition(65.5, 340);

    Texture cherrytexture;
    cherrytexture.loadFromFile("cherry.png");
    Sprite cherry;
    cherry.setTexture(cherrytexture);
    cherry.setScale(0.06, 0.06);
    cherry.setPosition(623, 545);

    Texture cointexture;
    cointexture.loadFromFile("coin.png");
    Sprite coin;
    coin.setTexture(cointexture);
    coin.setScale(0.03, 0.03);
    coin.setPosition(470, 510);



    Sprite coin2;
    coin2.setTexture(cointexture);
    coin2.setScale(0.03, 0.03);
    coin2.setPosition(188, 310);



    Sprite coin3;
    coin3.setTexture(cointexture);
    coin3.setScale(0.03, 0.03);
    coin3.setPosition(630, 190);



    Sprite coin4;
    coin4.setTexture(cointexture);
    coin4.setScale(0.03, 0.03);
    coin4.setPosition(72, 665);




    Texture Pactexture;
    Pactexture.loadFromFile("Pacman.PNG");
    Sprite Pacsprite(Pactexture);
    Pacsprite.setTextureRect(IntRect(0, 0, 65.5, 64));

    Pacsprite.setPosition(78.0f, 120.0f);

    Pacsprite.setScale(0.05, 0.05);
    Vector2f velocity = { 0, 0 };
    //  Pacsprite.setOrigin(Pacsprite.getLocalBounds().width, Pacsprite.getLocalBounds().height);

      //Pacsprite.setOrigin(Pacsprite.getLocalBounds().width / 2, Pacsprite.getLocalBounds().height / 2);

    Pacsprite.setOrigin(Pacsprite.getTextureRect().width / 2, Pacsprite.getTextureRect().height / 2);
    Vector2i Pacsprite_position(0, 0);


    float speed = 0.3f, timer = 0, delay = 0.15f, ghosts_speed = 0.02f;
    Clock clock;
    Pacsprite.setScale(0.5, 0.5);


    Texture ghost_red;
    ghost_red.loadFromFile("Ghosts_red.png");
    Sprite g1(ghost_red);
    g1.setTextureRect(IntRect(0, 0, 64, 64));
    g1.setScale(0.55, 0.55);


    Texture ghost_blue;
    ghost_blue.loadFromFile("Ghosts_blue.png");
    Sprite g2(ghost_blue);
    g2.setTextureRect(IntRect(0, 0, 64, 64));
    g2.setScale(0.55, 0.55);


    Texture ghost_lightblue;
    ghost_lightblue.loadFromFile("Ghosts_lightblue.png");
    Sprite g3(ghost_lightblue);
    g3.setTextureRect(IntRect(0, 0, 64, 64));
    g3.setScale(0.55, 0.55);


    Texture ghost_yellow;
    ghost_yellow.loadFromFile("Ghosts_yellow.png");
    Sprite g4(ghost_yellow);
    g4.setTextureRect(IntRect(0, 0, 64, 64));
    g4.setScale(0.55, 0.55);
    Texture edible_ghost;
    edible_ghost.loadFromFile("edible_ghost.png");


    bool isPaused = false;
    //Font font;
  //  if (!font.loadFromFile(".namecat/Namecat.ttf"))
   // {
    //    cerr << "Failed to load font" << endl;
    /////    return 1;
   // }

    RenderWindow window(VideoMode(800, 800), "Pacman");
    //Text pauseText("Press space to pause", font, 20);
   // pauseText.setFillColor(Color::White);
  //  pauseText.setPosition(window.getSize().x - pauseText.getLocalBounds().width - 10, 10);

    SoundBuffer coinbuffer;
    if (!coinbuffer.loadFromFile("coin.wav"))
    {
        return -1;
    }
    Sound coinsound;
    coinsound.setBuffer(coinbuffer);
    coinsound.setVolume(100.0f);



    SoundBuffer fruitbuffer;
    if (!fruitbuffer.loadFromFile("eat_fruit.wav"))
    {
        return -1;
    }
    Sound fruitsound;
    fruitsound.setBuffer(fruitbuffer);
    fruitsound.setVolume(100.0f);


    SoundBuffer ghostbuffer;
    if (!ghostbuffer.loadFromFile("ghost.wav"))
    {
        return -1;
    }
    Sound ghostsound;
    ghostsound.setBuffer(ghostbuffer);
    ghostsound.setVolume(100.0f);



    SoundBuffer eat_ghostbuffer;
  if (!eat_ghostbuffer.loadFromFile("eat_ghost.mp3"))
    {
       return -1;
    }
    Sound eat_ghostsound;
    eat_ghostsound.setBuffer(eat_ghostbuffer);
    eat_ghostsound.setVolume(100.0f);



    SoundBuffer level_upbuffer;
    if (!level_upbuffer.loadFromFile("level_up.wav"))
    {
        return -1;
    }
    Sound level_upsound;
    level_upsound.setBuffer(level_upbuffer);
    level_upsound.setVolume(100.0f);


    while (window.isOpen())
    {
        window.clear();

        if (score >= 500 && !level2)
        {
            level_upsound.play();
            level++;
            g1.setTexture(edible_ghost);
            g1.setTextureRect(IntRect(0, 0, 64, 64));
            g1.setScale(0.55, 0.55);
            level2 = true;
        }

        if (score >= 1000 && !level3)
        {
            level_upsound.play();
            level++;
            g2.setTexture(edible_ghost);
            g2.setTextureRect(IntRect(0, 0, 64, 64));
            g2.setScale(0.55, 0.55);
            level3 = true;
        }

        if (score >= 1500 && !level4)
        {
            level++;
            level_upsound.play();
            g3.setTexture(edible_ghost);
            g3.setTextureRect(IntRect(0, 0, 64, 64));
            g3.setScale(0.55, 0.55);
            level4 = true;
        }
        if (score >= 2000 && !level5)
        {
            level++;
            level_upsound.play();
            g4.setTexture(edible_ghost);
            g4.setTextureRect(IntRect(0, 0, 64, 64));
            g4.setScale(0.55, 0.55);
            level5 = true;
        }

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
            {

                isPaused = !isPaused;
            }
        }
        //  window.clear();

        if (!isPaused)
        {


            Vector2f pacPosition = Pacsprite.getPosition();

            if (pacPosition.x > g1.getPosition().x)
                x1 += ghosts_speed;
            else
                x1 -= ghosts_speed;

            if (pacPosition.y > g1.getPosition().y)
                y1 += ghosts_speed;
            else
                y1 -= ghosts_speed;

            // Update the position of g2
            if (pacPosition.x > g2.getPosition().x)
                x2 += ghosts_speed;
            else
                x2 -= ghosts_speed;

            if (pacPosition.y > g2.getPosition().y)
                y2 += ghosts_speed;
            else
                y2 -= ghosts_speed;

            // Update the position of g3
            if (pacPosition.x > g3.getPosition().x)
                x3 += ghosts_speed;
            else
                x3 -= ghosts_speed;

            if (pacPosition.y > g3.getPosition().y)
                y3 += ghosts_speed;
            else
                y3 -= ghosts_speed;

            // Update the position of g4
            if (pacPosition.x > g4.getPosition().x)
                x4 += ghosts_speed;
            else
                x4 -= ghosts_speed;

            if (pacPosition.y > g4.getPosition().y)
                y4 += ghosts_speed;
            else
                y4 -= ghosts_speed;


            if (lives == 0)
                window.close();
            if (Pacsprite.getGlobalBounds().intersects(g1.getGlobalBounds()))
            {
                if (level2)
                {
                    eat_ghostsound.play();
                    ghost1_eaten = true;
                    g1.setPosition(7000, 7000);
                }
                else
                {
                    Pacsprite.setPosition(78.0f, 120.0f);
                    ghostsound.play();
                    lives--;
                }
            }
            if (Pacsprite.getGlobalBounds().intersects(g2.getGlobalBounds()))
            {
                if (level3)
                {
                    eat_ghostsound.play();
                    ghost2_eaten = true;
                    g2.setPosition(7000, 7000);

                }
                else
                {
                    Pacsprite.setPosition(78.0f, 120.0f);
                    ghostsound.play();
                    lives--;
                }

            }
            if (Pacsprite.getGlobalBounds().intersects(g3.getGlobalBounds()))
            {
                if (level4)
                {
                    eat_ghostsound.play();
                    ghost3_eaten = true;
                    g3.setPosition(7000, 7000);

                }
                else
                {
                    Pacsprite.setPosition(78.0f, 120.0f);
                    ghostsound.play();
                    lives--;
                }
            }

            if (Pacsprite.getGlobalBounds().intersects(g4.getGlobalBounds()))
            {
                if (level5)
                {
                    eat_ghostsound.play();
                    ghost4_eaten = true;
                    g4.setPosition(7000, 7000);

                }
                else
                {
                    Pacsprite.setPosition(78.0f, 120.0f);
                    ghostsound.play();
                    lives--;
                }
            }

            if (Pacsprite.getGlobalBounds().intersects(strawberry.getGlobalBounds()))
            {
                score += 25;
                straw_eaten = true;
                strawberry.setPosition(7000, 7000);
                fruitsound.play();
            }

            if (Pacsprite.getGlobalBounds().intersects(cherry.getGlobalBounds()))
            {
                score += 30;
                cherry_eaten = true;
                cherry.setPosition(7000, 7000);
                fruitsound.play();
            }

            if (Pacsprite.getGlobalBounds().intersects(coin.getGlobalBounds()))
            {
                score += 50;
                coin_eaten = true;
                coin.setPosition(7000, 7000);
                fruitsound.play();
            }
            if (Pacsprite.getGlobalBounds().intersects(coin2.getGlobalBounds()))
            {
                score += 50;
                coin2_eaten = true;
                coin2.setPosition(7000, 7000);
                fruitsound.play();
            }
            if (Pacsprite.getGlobalBounds().intersects(coin3.getGlobalBounds()))
            {
                score += 50;
                coin3_eaten = true;
                coin3.setPosition(7000, 7000);
                fruitsound.play();
            }
            if (Pacsprite.getGlobalBounds().intersects(coin4.getGlobalBounds()))
            {
                score += 50;
                coin4_eaten = true;
                coin4.setPosition(7000, 7000);
                fruitsound.play();
            }
            /*window.clear();*/

            for (int i = 0; i < 19; i++)
            {
                for (int j = 0; j < 19; j++)
                {
                    if (board[i][j] == 0)
                    {
                        wall.setPosition(i * 40.0f + (800 - 19 * 40.0f) / 2, j * 40.0f + (800 - 19 * 40.0f) / 2);
                        window.draw(wall);
                    }
                    else if (board[i][j] == 1)
                    {
                        point.setPosition(i * 40.0f + (800 - 19 * 40.0f) / 2 + 13.0f, j * 40.0f + (800 - 19 * 40.0f) / 2 + 13.0f);
                        pathp.setPosition(i * 40.0f + (800 - 19 * 40.0f) / 2, j * 40.0f + (800 - 19 * 40.0f) / 2);

                        if (Pacsprite.getGlobalBounds().intersects(point.getGlobalBounds()))
                        {
                            point.setFillColor(Color::Blue);
                            coinsound.play();
                            board[i][j] = 2;
                            score += 15;
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
                        path.setPosition(i * 40.0f + (800 - 19 * 40.0f) / 2, j * 40.0f + (800 - 19 * 40.0f) / 2);
                        window.draw(path);
                    }
                }
            }



            Pacsprite_position.x = (Pacsprite.getPosition().x) / 40.5;
            Pacsprite_position.y = (Pacsprite.getPosition().y) / 40.5;

            //if (Keyboard::isKeyPressed(Keyboard::Up))
            //{
            //    if (board[Pacsprite_position.x][Pacsprite_position.y - 1] != 0)
            //    {
            //        velocity.x = 0;
            //        if (timer < 0)
            //        {
            //            //Pacsprite.setScale(1, -1);
            //            i++;
            //            i = i % 2;
            //           Pacsprite.setTextureRect(IntRect((i * 65.5), 192, 65.5, 64));
            //            velocity.y = -speed;
            //            timer = delay;
            //        }
            //        else
            //            timer -= deltaTime;
            //    }
            //}
            //else if (Keyboard::isKeyPressed(Keyboard::Down))
            //{
            //    if (board[Pacsprite_position.x][Pacsprite_position.y] != 0)
            //    {
            //        velocity.x = 0;
            //        if (timer < 0)
            //        {
            //            //Pacsprite.setScale(1, 1);
            //            i++;
            //            i = i % 2;
            //            Pacsprite.setTextureRect(IntRect((i * 65.5), 64, 65.5, 64));
            //            velocity.y = speed;
            //            timer = delay;
            //        }
            //        else
            //            timer -= deltaTime;
            //    }
            //}
            //else if (Keyboard::isKeyPressed(Keyboard::Left))
            //{
            //    if (board[Pacsprite_position.x - 1][Pacsprite_position.y] != 0)
            //    {
            //        velocity.y = 0;
            //        if (timer < 0)
            //        {
            //           // Pacsprite.setScale(-1, 1);
            //            i++;
            //            i = i % 2;
            //          Pacsprite.setTextureRect(IntRect((i * 65.5), 128, 65.5, 64));
            //            velocity.x = -speed;
            //            timer = delay;
            //        }
            //        else
            //            timer -= deltaTime;
            //    }
            //}
            //else if (Keyboard::isKeyPressed(Keyboard::Right))
            //{
            //    if (board[Pacsprite_position.x][Pacsprite_position.y] != 0)
            //    {
            //        velocity.y = 0;
            //        if (timer < 0)
            //        {
            //           // Pacsprite.setScale(1, 1);
            //            i++;
            //            i = i % 2;
            //           Pacsprite.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));
            //            velocity.x = speed;
            //            timer = delay;
            //        }
            //        else
            //            timer -= deltaTime;
            //    }
            //}
            //else
            //{
            //    velocity.x = 0;
            //    velocity.y = 0;
            //}


            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                if (board[Pacsprite_position.x][Pacsprite_position.y] != 0)
                {
                    velocity.y = 0;
                    if (timer < 0)
                    {

                        i++;
                        i = i % 2;
                        Pacsprite.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));
                        velocity.x = speed;
                        g1.setTextureRect(IntRect((i * 64), 0, 64, 64));
                        g2.setTextureRect(IntRect((i * 64), 0, 64, 64));
                        g3.setTextureRect(IntRect((i * 64), 0, 64, 64));
                        g4.setTextureRect(IntRect((i * 64), 0, 64, 64));
                        timer = delay;
                    }
                    else
                        timer -= deltaTime;
                }
                else
                {
                    Pacsprite.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));

                    velocity.x = 0;
                    velocity.y = 0;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                if (board[Pacsprite_position.x - 1][Pacsprite_position.y] != 0)
                {
                    velocity.y = 0;
                    if (timer < 0)
                    {

                        i++;
                        i = i % 2;
                        Pacsprite.setTextureRect(IntRect((i * 65.5), 128, 65.5, 64));
                        velocity.x = -speed;
                        g1.setTextureRect(IntRect((i * 64), 0, 64, 65));
                        g2.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));
                        g3.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));
                        g4.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));
                        timer = delay;
                    }
                    else
                        timer -= deltaTime;
                }
                else
                {
                    Pacsprite.setTextureRect(IntRect((i * 65.5), 128, 65.5, 64));
                    velocity.x = 0;
                    velocity.y = 0;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (board[Pacsprite_position.x][Pacsprite_position.y] != 0)
                {
                    velocity.x = 0;
                    if (timer < 0)
                    {

                        i++;
                        i = i % 2;
                        Pacsprite.setTextureRect(IntRect((i * 65.5), 64, 65.5, 64));
                        velocity.y = speed;
                        g1.setTextureRect(IntRect((i * 64), 0, 64, 64));
                        g2.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));
                        g3.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));
                        g4.setTextureRect(IntRect((i * 65.5), 0, 65.5, 64));
                        timer = delay;
                    }
                    else
                        timer -= deltaTime;
                }
                else
                {
                    Pacsprite.setTextureRect(IntRect((i * 65.5), 64, 65.5, 64));
                    velocity.x = 0;
                    velocity.y = 0;
                }
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (board[Pacsprite_position.x][Pacsprite_position.y - 1] != 0)
                {
                    velocity.x = 0;
                    if (timer < 0)
                    {

                        i++;
                        i = i % 2;

                        Pacsprite.setTextureRect(IntRect((i * 65.5), 192, 65.5, 64));
                        velocity.y = -speed;
                        g1.setTextureRect(IntRect((i * 65), 0, 65, 65));
                        g2.setTextureRect(IntRect((i * 65.5), 0, 61, 64));
                        g3.setTextureRect(IntRect((i * 65.5), 0, 61, 64));
                        g4.setTextureRect(IntRect((i * 65.5), 0, 61, 64));
                        timer = delay;
                    }
                    else
                        timer -= deltaTime;
                }
                else
                {
                    Pacsprite.setTextureRect(IntRect((i * 65.5), 192, 65.5, 64));
                    velocity.x = 0;
                    velocity.y = 0;
                }
            }
            else
            {
                velocity.x = 0;
                velocity.y = 0;
            }

            Pacsprite.move(velocity);
            g1.setPosition(x1, y1);
            g2.setPosition(x2, y2);
            g3.setPosition(x3, y3);
            g4.setPosition(x4, y4);



            window.draw(Pacsprite);

            if (!ghost1_eaten)
            {
                window.draw(g1);
            }
            if (!ghost2_eaten)
            {
                window.draw(g2);
            }
            if (!ghost3_eaten)
            {
                window.draw(g3);
            }
            if (!ghost4_eaten)
            {
                window.draw(g4);
            }
            if (!straw_eaten)
            {
                window.draw(strawberry);
            }
            if (!cherry_eaten)
            {
                window.draw(cherry);
            }
            if (!coin_eaten)
            {
                window.draw(coin);
            }
            if (!coin2_eaten)
            {
                window.draw(coin2);
            }
            if (!coin3_eaten)
            {
                window.draw(coin3);
            }
            if (!coin4_eaten)
            {
                window.draw(coin4);
            }
        }
        window.display();
        deltaTime = clock.getElapsedTime().asSeconds();
        cout << score << endl;
        cout << level << endl;

    }
    return 0;
}