#pragma once
#include <SDL.h>
#include <string>
class rect;

class renderWindow{
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool running;

	int fps;
	Uint32 startTick;
public:
	renderWindow(const char* title, int w, int h);

	void setFPS(int newFPS);
	void clear();
	void display();
	bool isOpen();
	void close();

	void draw(const rect& obj);
	void setTitle(std::string title);

	~renderWindow();
};