#include "food.h"
#include <windows.h>
void gotoxy2(HANDLE hOut2, int x, int y)
{
	COORD pos;
	pos.X = x;             // abscissa
	pos.Y = y;            //ordinate
	SetConsoleCursorPosition(hOut2, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);//Defines the display handle variable


Food::Food(Wall & tempWall) : wall(tempWall)
{

}

void Food::setFood()
{
	while (true)
	{
		foodX = rand() % (Wall::ROW - 2) + 1;
		foodY = rand() % (Wall::COL - 2) + 1;

		//If the random location is the snakehead or the snake, the random number will be regenerated
		if (wall.getWall(foodX, foodY) == ' ')
		{
			
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOut2, foodY * 2, foodX);
			cout << "#";
			break;
		}
	}
}
