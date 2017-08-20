#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <ctime>
#include <conio.h>
#include <Windows.h>

void gotoxy(HANDLE hOut, int x, int y)
{
	COORD pos;
	pos.X = x;             // abscissa
	pos.Y = y;            //ordinate
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//Defines the display handle variable


int main(){

	//Add random seeds
	srand((unsigned int)time(NULL));

	//Death note
	bool isDead = false;

	char preKey = NULL;

	Wall wall;
	wall.initWall();
	wall.drawWall();
	
	Food food(wall);
	food.setFood();

	Snake snake(wall, food);
	snake.initSnake();


	gotoxy(hOut, 0, Wall::ROW);
	cout << "得分：" << snake.getScore() << "分" << endl;

	

	//Accept user input


	while (!isDead)
	{
		char key = _getch();

		//If you hit left key for the first time, you can't activate the game
		// Determine the last time you moved
		if (preKey == NULL && key == snake.LEFT)
		{
			continue;
		}

		do 
		{
			if (key == snake.UP || key  == snake.DOWN || key == snake.LEFT || key == snake.RIGHT)
			{
				//Determine if this button is in conflict with the last one
				if ( (key == snake.LEFT && preKey == snake.RIGHT)  ||
					(key == snake.RIGHT && preKey == snake.LEFT) ||
					(key == snake.UP && preKey == snake.DOWN) ||
					(key == snake.DOWN && preKey == snake.UP))
				{
					key = preKey;
				}
				else
				{
					preKey = key; //It's not the conflict button that can be updated
				}


				if (snake.move(key) == true)
				{
					//Mobile success code
					gotoxy(hOut,0, Wall::ROW);
				
					cout << "得分：" << snake.getScore() << "分" << endl;
					Sleep(snake.getSleepTime());
				}
				else
				{
					isDead = true;
					break;
				}
			}
			else
			{
				key = preKey; //Force the error button to become the last moving direction
			}
			

		} while (!_kbhit()); //Returns 0 when there is no keyboard input

	
	}


	system("pause");
	return EXIT_SUCCESS;
}