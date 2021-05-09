#pragma once
#include <SDL.h>
#include <list>

#include "rect.h"
#include "renderWindow.h"

class snake{
	int direction;
	int prevDirection;
	vector2 hitPoint;
	int speed;
	int size;
	bool gameOver;
	list<rect> body;
	int score;
	bool inputLock;
	bool delay;

	rect morsel;

	void move();
	void moveForward();
	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
	void moveTail();

	void grow();//grow snake by 1 unit
	bool borderCollision();//collision with window borders
	bool selfCollision();
	bool morselCollision();
	int segmentDirection(const rect& segment);//direction of particular segment
	void setColor(int r, int g, int b, int a);

	void createMorsel();
public:
	snake();
	void restart();

	void input(SDL_Event event);
	bool update();

	void drawTo(renderWindow& window);
	int getScore();
	~snake();
};

