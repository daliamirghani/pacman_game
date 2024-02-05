#include "MainMenu.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

MainMenu::MainMenu(float width, float hight)
{

	font.loadFromFile("Namecat.ttf");

	Menu[0].setFont(font);
	Menu[0].setFillColor(Color{ 255, 204, 0 });
	Menu[0].setString("Start a game");
	Menu[0].setCharacterSize(50);
	Menu[0].setPosition(Vector2f(250, hight / (4) + 200));


	Menu[1].setFont(font);
	Menu[1].setFillColor(Color::White);
	Menu[1].setString("About us");
	Menu[1].setCharacterSize(50);
	Menu[1].setPosition(Vector2f(300, hight / (4) + 250));


	Menu[2].setFont(font);
	Menu[2].setFillColor(Color::White);
	Menu[2].setString("Exit");
	Menu[2].setCharacterSize(50);
	Menu[2].setPosition(Vector2f(350, hight / (4) + 300));

	selected = 0;

}
MainMenu::~MainMenu() {}
void MainMenu::setSelected(int n)
{
	selected = n;
}
void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(Menu[i]);
	}
}

void MainMenu::movedown()
{
	if (selected + 1 <= 3) //my arr is 0 baised so I incremented 1 now it selected 1 from 3
	{
		Menu[selected].setFillColor(Color::White);
		selected++;            //because I'm moving down so I wanna increment the selected to select the next option
		if (selected == 3) //the last option 
		{
			selected = 0;   //return to the 1st option
		}
		Menu[selected].setFillColor(Color{ 255, 204, 0 });
	}
}

void MainMenu::moveup()
{
	if (selected - 1 >= -1)  ///cheak if the option isn't  the 1st option (Start a new game) (index 0)
	{
		Menu[selected].setFillColor(Color::White);
		selected--;                //move to the upper option
		if (selected == -1)  //if I decremented and now I'm -1 (index 0) then back to index 2(option 3(Exit))
		{
			selected = 2;
		}
		Menu[selected].setFillColor(Color{ 255, 204, 0 });
	}
}