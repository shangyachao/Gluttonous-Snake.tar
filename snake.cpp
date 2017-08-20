#include "snake.h"
#include <windows.h>
void gotoxy1(HANDLE hOut1, int x, int y)
{
	COORD pos;
	pos.X = x;             // abscissa
	pos.Y = y;            //ordinate
	SetConsoleCursorPosition(hOut1, pos);
}
HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);//Defines the display handle variable


Snake::Snake(Wall & tempWall, Food & tmpFood) : wall(tempWall), food(tmpFood)
{
	pHead = NULL;
	isRool = false;
}


void Snake::initSnake()
{
	destroyPoint();

	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}

//Destroy all nodes
void Snake::destroyPoint()
{
	Point * pCur = pHead;

	while (pHead != NULL)
	{
		pCur = pHead->next;
		delete pHead;

		pHead = pCur;
	}
}

void Snake::addPoint(int x, int y)
{
	//Create a new node
	Point * newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	newPoint->next = NULL;

	//If the head does not change to the body

	if (pHead != NULL)
	{
		wall.setWall(pHead->x, pHead->y, '=');

		gotoxy1(hOut1, pHead->y * 2, pHead->x);
		cout << "=";

	}

	newPoint->next = pHead;

	pHead = newPoint; //Update the head

	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy1(hOut1, pHead->y * 2, pHead->x);
	cout << "@";


}

//Delete Node
void Snake::delPoint()
{
	
	//Delete operations only after two nodes
	if (pHead == NULL || pHead->next == NULL)
	{
		return;
	}

	Point * pCur = pHead->next;
	Point * pPre = pHead;

	while (pCur->next !=NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	//End node

	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy1(hOut1, pCur->y * 2, pCur->x);
	cout << " ";

	delete pCur;
	pCur = NULL;
	pPre->next = NULL;

}

bool Snake::move(char key)
{
	int x = pHead->x;
	int y = pHead->y; 

	switch (key)
	{
	case UP:
		x--;
		break;
	case DOWN :
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	//If it's the tail, it shouldn't be dead
	Point * pCur = pHead->next;
	Point * pPre = pHead;

	while (pCur->next != NULL)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	if (pCur->x == x && pCur->y == y)
	{
		//Tail cycle
		isRool = true;
	}
	else
	{
		//Determine whether the user's arrival location is successful
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=')
		{
			addPoint(x, y);
			delPoint();
			system("cls");
			wall.drawWall();
			cout << "µÃ·Ö£º" << getScore() << "·Ö" << endl;
			cout << "GAME OVER!!!" << endl;
			return false;
		}
	}



	//There are two kinds of mobile success
	//Eat the food //  The food was not eaten
	if (wall.getWall(x,y) == '#')
	{
		addPoint(x, y);

		//reorder food
		food.setFood();
	}
	else
	{
		addPoint(x, y);
		delPoint();
		if (isRool == true)
		{
			wall.setWall(x, y, '@');
			gotoxy1(hOut1, 2 * y, x);
			cout << "@";
		}
		
	}

	return true;
}

int Snake::getSleepTime()
{
	int sleepTime = 0;

	int size = countList();
	if ( size < 5)
	{
		sleepTime = 300;
	}
	else if (size >=5 && size <=8)
	{
		sleepTime = 200;
	}
	else
	{
		sleepTime = 100;
	}
	return sleepTime;
}

int Snake::countList()
{
	int size = 0;
	Point * curPoint = pHead;
	while (curPoint != NULL)
	{
		size++;

		curPoint = curPoint->next;
	}
	return size;
}

int Snake::getScore()
{
	int size = countList();

	int score = (size -3) * 100;

	return score;
}

