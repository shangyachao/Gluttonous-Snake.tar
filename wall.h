#ifndef _WALL_HEAD
#define _WALL_HEAD
//#pragma  once

#include <iostream>
using namespace std;

class Wall
{
public:
	enum {
		ROW = 26,
		COL = 26
	};

	
	//Initial wall
	void initWall();

	//Draw the walls
	void drawWall();

	//Sets the contents of the two-dimensional array according to the index
	void setWall(int x, int y, char c);

	//Gets the symbol for the current position based on the index
	char getWall(int x, int y);

private:
	char gameArray[ROW][COL];
};




#endif