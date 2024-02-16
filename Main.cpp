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
    //log("right");
}

void turnL()
{
    API::turnLeft();
    angle = filt(angle - 90);
    //log("left");
}

void forward()
{
    API::moveForward();
    pos += num(angle);
    //API::setColor(pos / 16, pos % 16, 'G');
    //log("forward");
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
        y = - 1;
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
        API::setColor(pos / 16, pos % 16, 'G');
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
    for (int i = arr_size; i >= 0; i--)
    {
        move(arr[i]);
    }
}

void dijkstra(int _begin, int _end)
{
    std::deque<int>  dequeue;
    bool visited[SIZE];
    dequeue.push_back(_begin);
    int way[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        way[i] = 10000;
        visited[i] = 0;
    }
    way[_begin] = 0;
    while (dequeue.size() != 0 && dequeue.front() != _end)
    {
        int i = dequeue.front();
        log("checing"+to_string(i));
        visited[i] = 1;
        dequeue.pop_front();
        if (maze[i][i + 1] > 0 && !visited[i + 1])
        {
             dequeue.push_back(i + 1);
            if (way[i + 1] > way[i] + maze[i][i + 1])
            {
                way[i + 1] = way[i] + maze[i][i + 1];
                log("^");
            }
        }
        if (maze[i][i - 1] > 0 && !visited[i - 1])
        {
            dequeue.push_back(i - 1);
            if (way[i - 1] > way[i] + maze[i][i - 1])
            {
                way[i - 1] = way[i] + maze[i][i - 1];
                log("|");
            }
        }
        if (i - LENGTH >= 0 && maze[i][i - LENGTH] > 0 && !visited[i - LENGTH])
        {
            dequeue.push_back(i - LENGTH);
            if (way[i - LENGTH] > way[i] + maze[i][i - LENGTH])
            {
                way[i - LENGTH] = way[i] + maze[i][i - LENGTH];
                log("<");
            }
        }
        if (i + LENGTH < SIZE && maze[i][i + LENGTH] > 0 && !visited[i + LENGTH])
        {
            dequeue.push_back(i + LENGTH);
            if (way[i + LENGTH] > way[i] + maze[i][i + LENGTH])
            {
                way[i + LENGTH] = way[i] + maze[i][i + LENGTH];
                log(">");
            }
        }
    }
    if(dequeue.size())
        log("front gueue" + to_string(dequeue.front()));
    log("end");
    int end = _end;

    int points[SIZE];
    points[0] = _end;
    int k = 0;
    while (end != _begin)
    {
        if (end % 16 != 15 && way[end] - maze[end][end + 1] == way[end + 1])
        {
            end = end + 1;
        }
        else if (end % 16 != 0 && way[end] - maze[end][end - 1] == way[end - 1])
        {
            end = end - 1;
        }
        else if (end + LENGTH < SIZE && way[end] - maze[end][end + LENGTH] == way[end + LENGTH])
        {
            end = end + LENGTH;
        }
        else if (end - LENGTH >= 0 && way[end] - maze[end][end - LENGTH] == way[end - LENGTH])
        {
            end = end - LENGTH;
        }
        else
        {
            log("algoritm_error");
        }
        k++;
        log("to points" + to_string(end));
        points[k] = end;
    }
    run(points, k);

    


}


void map_maze()
{
    bool visited[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        visited[i] = 0;
    }
    std::deque<int>  dequeue;
    dequeue.push_front(0);
    while (!dequeue.empty())
    {
        int i = dequeue.front();
        if (visited[i] == 1)
        {
            dequeue.pop_front();
        }
        else
        {
            if (i != pos)
            {
                API::setColor(i / 16, i % 16, 'R');
                dijkstra(pos, i);
            }
            visited[i] = 1;
            API::setColor(i / 16, i % 16, 'G');
            dequeue.pop_front();
            int j;
            if (!API::wallLeft())
            {
                j = pos + num(filt(angle - 90));
                if (!visited[j])
                {
                    API::setColor(j / 16, j % 16, 'B');
                    dequeue.push_front(j);
                }
                maze[i][j] = 1;
                maze[j][i] = 1;
                //log("<" + to_string(j));

            }
            if (!API::wallFront())
            {
                j = pos + num(angle);
                if (!visited[j])
                {
                    API::setColor(j / 16, j % 16, 'B');
                    dequeue.push_front(j);
                }
                maze[i][j] = 1;
                maze[j][i] = 1;
                //log("_^_");
            }
            if (!API::wallRight())
            {
                j = pos + num(filt(angle + 90));
                if (!visited[j])
                {
                    API::setColor(j / 16, j % 16, 'B');
                    dequeue.push_front(j);
                }
                maze[i][j] = 1;
                maze[j][i] = 1;
                //log(">");
            }
        }

    }

}



int main(int argc, char* argv[]) 
{
    log(" not Running...");
    API::setColor(0, 0, 'G');
    API::setText(0, 0, "abc");
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            maze[i][j] = 0;
        }
    }
    map_maze();
    dijkstra(pos, 0);
    dijkstra(0, 16*8+8);
    log("You win, darling");
}
