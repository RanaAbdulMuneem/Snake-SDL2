#pragma once
#include <SDL.h>
#include "renderWindow.h"
#include "vector2.h"

class rect{
	friend class renderWindow;
	SDL_Rect box;
	int rgba[4];
public:
	rect();
	rect(int x, int y, int w, int h);
	rect(const rect& obj);
	
	void setX(int x);
	void setY(int y);
	void setPosition(vector2 pos);
	void setW(int w);
	void setH(int h);
	void setSize(vector2 size);

	vector2 getPosition();
	vector2 getSize() const;

	void moveX(int x);
	void moveY(int y);
	void growW(int w);
	void growH(int h);
	void move(vector2 pos);
	void grow(vector2 size);

	bool contains(const vector2& point);

	void setColor(int r, int g, int b, int a);
};

