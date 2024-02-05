#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class MainMenu
{
public:
    Text Menu[3];
    MainMenu(float width, float hight);
    void draw(RenderWindow& window);
    void moveup();
    void movedown();
    void setSelected(int n);
    int Pressed()
    {
        return selected;
    }

    ~MainMenu();

private:
    int selected;
    Font font;

};