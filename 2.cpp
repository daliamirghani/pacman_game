#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<ctime>
#include<cstdlib>
#include<string>
#include "MainMenu.h"
#include<iomanip>
using namespace sf;
using namespace std;
Clock gameclock;

float timer = 0.0f;
float delay = 0.5f;
float deltaTime = 0;

//function to make ghosts go to random place after touching
void resetGhostPosition(Sprite& ghost)
{
	float x = rand() % 800;
	float y = rand() % 800;
	ghost.setPosition(x, y);
}

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

int score = -15;
int lives = 3;
int level = 1;
bool level2 = false;
bool level3 = false;
bool level4 = false;
bool level5 = false;


//function to create a name
Text createText(Font& font, const string& str, unsigned int characterSize, const sf::Color& fillColor, float x, float y) {
	Text text;
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(characterSize);
	text.setFillColor(fillColor);
	text.setPosition(x, y);
	return text;
}



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
int game();
Text createText(Font& font, const string& str, unsigned int characterSize, const sf::Color& fillColor, float x, float y);

int main()
{

	RenderWindow window(VideoMode(800, 800), "Pac_Man!", Style::Close);
	MainMenu menu(800, 800);
	Texture menubackground;
	menubackground.loadFromFile("bg_pacman.jpg");
	Sprite bg; //bg for background
	bg.setTexture(menubackground);
	bg.setScale(0.5, 0.5);
	int pagenum = 1000; //To know I had selsected which page?

	bool isPaused = false;
    while (true) {
        if (pagenum == 1000) {
            while (window.isOpen())
            {
                // clock.restart();
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                        break;
                    }
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space)
                    {

                        isPaused = !isPaused;
                    }
                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::Up)
                        {
                            menu.moveup();
                            break;
                        }
                    }
                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::Down)
                        {
                            menu.movedown();
                            break;
                        }
                    }
                    //chose page
                    if (event.key.code == Keyboard::Return)
                    {
                        if (menu.Pressed() == 0)
                        {
                            window.close();
                            pagenum = 0;   //option start a new game
                        }
                        if (menu.Pressed() == 1)
                        {
                            window.close();
                            pagenum = 1;   //option about us
                        }
                        if (menu.Pressed() == 2)
                        {
                            window.close();
                            pagenum = 2;   //option exit
                        }
                    }
                }
                window.clear();
                window.draw(bg);
                menu.draw(window);
                window.display();


            }




            if (pagenum == 0)
                game();



            else  if (pagenum == 1) //option about us
            {
                RenderWindow window_about(VideoMode(800, 800), "Options", Style::Close);
                MainMenu menu(800, 800);
                Font font;
                Texture menubackground;
                menubackground.loadFromFile("bg_pacman.jpg");
                Sprite bg; //bg for background
                bg.setTexture(menubackground);
                bg.setScale(0.5, 0.5);
                font.loadFromFile("Namecat.ttf");

                Text text1 = createText(font, "Dalia Ahmed                 Gehad Ebrahim", 24, Color(255, 204, 0), 180.f, 400.f);
                Text text2 = createText(font, "Habiba Mokhtar              Tasneem Shelah", 24, Color(255, 204, 0), 170.f, 600.f);
                Text text3 = createText(font, "               Lina Fadel", 24, Color(255, 204, 0), 250.f, 500.f);
                Text text4 = createText(font, "Creators", 50, Color::Red, 285.f, 80.f);
                Text text5 = createText(font, "About Us", 60, Color::Red, 270.f, 20.f);
                while (window_about.isOpen()) {
                    Event event;
                    while (window_about.pollEvent(event)) {
                        if (event.type == Event::Closed) {
                            window_about.close();
                        }
                    }

                    window_about.clear();
                    window_about.draw(bg);
                    window_about.draw(text1);
                    window_about.draw(text2);
                    window_about.draw(text3);
                    window_about.draw(text4);
                    window_about.draw(text5);
                    window_about.display();
                }
            }

            if (pagenum == 2)                  //option exit
            {
                break;

            }
        }


    }
	return 0;
}

int game() {
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
    bool isWon = false;
    bool isLost = false;
    Font font;
    if (!font.loadFromFile("Namecat.ttf"))
    {
        cerr << "Failed to load font" << endl;
        return 1;
    }

    RenderWindow window(VideoMode(800, 800), "Pacman");

    Text winText = createText(font, "You Won!", 50, Color::Green, 300, 350);
    Text loseText = createText(font, "You Lost :(", 50, Color::Red, 260, 350);
    Text pauseText = createText(font, "Press space to unpause", 50, Color::Yellow, 120, 350);

    /*    pauseText.setFillColor(Color::White);
        pauseText.setPosition(window.getSize().x - pauseText.getLocalBounds().width - 10, 10);*/

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
    if (!eat_ghostbuffer.loadFromFile("eat_ghost.wav"))
    {
        return -1;
    }
    Sound eat_ghostsound;
    eat_ghostsound.setBuffer(eat_ghostbuffer);
    eat_ghostsound.setVolume(100.0f);

    SoundBuffer win;
    if (!win.loadFromFile("win.wav"))
    {
        return -1;
    }
    Sound winsound;
    winsound.setBuffer(win);
    winsound.setVolume(100.0f);

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
        Text scoreText = createText(font, "Score: " + to_string(score), 50, Color::Yellow, 20, 20);
        Text livesText = createText(font, "Lives: " + to_string(lives), 50, Color::Yellow, 600, 20);

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

        if (isPaused)
            window.draw(pauseText);
        else if (isWon)
            window.draw(winText);
        else if (isLost)
            window.draw(loseText);
        else
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
                    ghostsound.play();
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
                    //eat_ghostsound.play();
                    ghost4_eaten = true;
                    winsound.play();
                    g4.setPosition(7000, 7000);
                    isWon = true;




                }
                else
                {
                    Pacsprite.setPosition(78.0f, 120.0f);
                    ghostsound.play();
                    lives--;
                }
            }
            if (lives == 0)
                isLost = true;
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
            window.draw(scoreText);
            window.draw(livesText);

        }

        window.display();
        deltaTime = clock.getElapsedTime().asSeconds();
        cout << score << endl;
        cout << level << endl;

    }
}
