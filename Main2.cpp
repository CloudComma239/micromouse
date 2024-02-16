#include <iostream>
#include <string>
#include <list>
#include <queue>
#include <Math.h>

#include "API.h"

#define SIZE 16*16
#define LENGTH 16
#define PI 3.14159265359

using namespace std;

int angle = 0;
int pos = 0;
int maze[SIZE][SIZE];

void log(const std::string& text)
{
    std::cerr << text << std::endl;
}

int filt(int _angle)
{
    if (_angle >= 360)
        return _angle - 360;
    if (_angle < 0)
        return _angle + 360;
    return _angle;
}

int num(int _angle)
{
    if (_angle == 0)
    {
        return 1;
    }
    else if (_angle == 180)
    {
        return -1;
    }
    else if (_angle == 270)
    {
        return -LENGTH;
    }
    else // (_angle == 90)
    {
        return LENGTH;
    }
}

void turnR()
{
    API::turnRight();
    angle = filt(angle + 90);
    log("right");
}

void turnL()
{
    API::turnLeft();
    angle = filt(angle - 90);
    log("left");
}

void forward()
{
    API::moveForward();
    pos += num(angle);
    API::setColor(pos / 16, pos % 16, 'G');
    log(to_string(pos));
    log(to_string(angle));
    log("forward");
}

void move(int goal)
{
    float x = 0, y = 0;
    if (goal - pos == 1) //Вверх в СО лабиринта
    {
        x = 0;
        y = 1;
    }
    else if (goal - pos == -1)//Вниз в СО лабиринта
    {
        x = 0;
        y = -1;
    }
    else if (goal - pos == -LENGTH)//Влево в СО лабиринта
    {
        x = -1;
        y = 0;
    }
    else if (goal - pos == LENGTH)//Вправо в СО лабиринта
    {
        x = 1;
        y = 0;
    }
    else if (goal - pos == 0)
    {
        log("here");
    }
    else //Цель не соседняя клетка
    {
        log("Impossible goal");
    }

    //log(to_string(x) + " " + to_string(y));

    int _x = round(x * cos(angle * PI / 180) - y * sin(angle * PI / 180));
    int _y = round(x * sin(angle * PI / 180) + y * cos(angle * PI / 180));

    //log(to_string(_x) + " " + to_string(_y));

    if (_y == 1)    //Вверх в СО робота
    {
        forward();
    }
    else if (_y == -1)  //Вниз в СО робота
    {
        turnL();
        turnL();
        forward();
    }
    else if (_x == -1)  //Влево в СО робота
    {
        turnL();
        forward();
    }
    else if (_x == 1)  //Вправо в СО робота
    {
        turnR();
        forward();
    }
}

void run(int arr[], int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        move(arr[i]);
    }
}

int main(int argc, char* argv[]) 
{
    log("not Running...");
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
    int points[] = { 0,1,2,18,17,16,17, 18, 34,33,32,33, 49,48,16*4,16*5,16*6,16*7,16*8,16*9,16*10,16*11,16*12,16*13,16*14,16*15,16*15+1,16*14+1,16 * 13 + 1,16 * 12 + 1,16 * 11 + 1,16 * 10 + 1,16 * 9 + 1,16 * 8 + 1,16 * 7 + 1,16 * 6 + 1,16 * 5 + 1,16 * 4 + 1,16 * 4 + 2,16 * 4 + 3,16 * 4 + 4,16 * 4 + 5,16 * 4 + 6,16 * 3 + 6,16 * 2 + 6 ,16*2  + 7,16 * 3 + 7,16 * 4 + 7,16 * 5 + 7 };
    run(points,14+12+12+11);
    for (int i = 7; i > 1; i--)
    {
        move(16 * 5 + i);
    }
    for (int i = 5; i < 15; i++)
    {
        move(16 *i + 2);
    }
    move(16 * 14 + 3);
    for (int i = 14; i > 5; i--)
    {
        move(16 * i + 3);
    }

    move(16 * 6 + 4);
    for (int i = 6; i < 16; i++)
    {
        move(16 * i + 4);
    }
    int g[] = { 16 * 15 + 3,16 * 15 + 2,16 * 15 + 3,16 * 15 + 4,16 * 15 + 5,16 * 15 + 6,16 * 15 + 7 };
    run(g,7);
    for (int i = 15; i > 8; i--)
    {
        move(16 * i + 7);
    }
    move(16 * 9 + 8);
    for (int i = 9; i < 14; i++)
    {
        move(16 * i + 8);
    }
    move(16 * 13 + 9);
    for (int i = 13; i > 9; i--)
    {
        move(16 * i + 9);
    }
    move(16 * 9 + 10);
    for (int i = 9; i < 14; i++)
    {
        move(16 * i + 10);
    }
    move(16 * 13 + 11);
    for (int i = 13; i > 9; i--)
    {
        move(16 * i + 11);
    }
    move(16 * 9 + 12);
    for (int i = 9; i < 15; i++)
    {
        move(16 * i + 12);
    }
    for (int i = 11; i > 7; i--)
    {
        move(16 * 14 + i);
    }
    for (int i = 8; i < 14; i++)
    {
        move(16 * 14 + i);
    }
    for (int i = 13; i > 8; i--)
    {
        move(16 * i + 13);
    }
    move(16 * 9 + 12);
    move(16 * 8 + 12);
    move(16 * 8 + 13);
    for (int i = 8; i > 4; i--)
    {
        move(16 * i + 13);
    }
    for (int i = 5; i < 9; i++)
    {
        move(16 * i + 13);
    }
    for (int i = 8; i > 4; i--)
    {
        move(16 * i + 12);
    }
    for (int i = 11; i > 7; i--)
    {
        move(16 * 5 + i);
    }
    for (int i = 5; i > 0; i--)
    {
        move(16 * i + 8);
    }
    for (int i = 1; i < 5; i++)
    {
        move(16 * i + 9);
    }
    for (int i = 10; i < 15; i++)
    {
        move(16 * 4 + i);
    }
    for (int i = 5; i < 16; i++)
    {
        move(16 * i + 14);
    }

    for (int i = 13; i > 7; i--)
    {
        move(16 * 15 + i);
    }

    for (int i = 9; i < 16; i++)
    {
        move(16 * 15 + i);
    }
    for (int i = 14; i > 2; i--)
    {
        move(16 * i + 15);
    }
    move(16 * 3 + 14);
    move(16 * 2 + 14);
    move(16 * 2 + 15);
    move(16 * 2 + 14);
    move(16 * 2 + 13);
    move(16 * 1 + 13);
    move(16 * 1 + 14);
    move(16 * 1 + 15);
    move(16 * 1 + 14);
    move(16 * 1 + 13);
    move(16 * 0 + 13);
    move(16 * 0 + 14);
    move(16 * 0 + 15);
    move(16 * 0 + 14);
    move(16 * 0 + 13);
    move(16 * 1 + 13);
    move(16 * 1 + 12);
    for (int i = 12; i > 2; i--)
    {
        move(i);
    }

    move(16 * 1 + 3);
    move( 3);
    move(4);
    move(16 * 1 + 4);
    move(16 * 2 + 4);
    move(16 * 2 + 3);
    move(16 * 2 + 4);
    move(16 * 1 + 4);
    move(4);
    move(5);
    for (int i = 0; i < 4; i++)
    {
        move(16 * i + 5);
    }
    for (int i = 5; i > 1; i--)
    {
        move(16 * 3 + i);
    }
    for (int i = 2; i < 6; i++)
    {
        move(16 * 3 + i);
    }
    for (int i = 3; i > -1; i--)
    {
        move(16 * i + 5);
    }
    for (int i = 5; i < 11; i++)
    {
        move(i);
    }
    for (int i = 1; i < 4; i++)
    {
        move(16 * i + 10);
    }
    for (int i = 11; i < 15; i++)
    {
        move(16 * 3 + i);
    }
    move(16*2+14);
    move(16 * 2 + 13);
    move(16  + 13);
    move(16  + 12);
    move(12);
    move(11);
    move(16 + 11);
    move(16*2 + 11);
    move(16*2 + 12);
    move(16 * 2 + 13);
    move(16 * 2 + 14);
    move(16 * 3 + 14);
    for (int i = 3; i < 16; i++)
    {
        move(16 * i + 15);
    }
    move(16 * 15 + 15);
    move(16 * 15 + 14);
    for (int i = 15; i > 3; i--)
    {
        move(16 * i + 14);
    }

}
