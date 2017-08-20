#pragma  once
#include <iostream>
#include "wall.h"
#include "food.h"
using namespace std;

class Snake
{
public:
	Snake(Wall & tempWall, Food & food );

	enum { UP = 'w', DOWN = 's', LEFT = 'a' , RIGHT = 'd'};

	//node
	struct Point
	{
		//data field
		int x;
		int y;
		//pointer field
		Point * next;
	};

	//Initialize the snake
	void initSnake();

	// Destruction of the node
	void destroyPoint();

	// Add node
	void addPoint(int x,int y);


	// Delete Node
	void delPoint();

	//Mobile snake operation
	//The return value represents the success of the move
	bool move(char key);


	//cheat diff
	//Get refresh time
	int getSleepTime();
	//Get a snake
	int countList();

	//To get scores
	int getScore();

	Point * pHead;

	Wall & wall;

	Food & food;

	bool isRool; //≈–∂œ—≠ª∑±Í æ
};


