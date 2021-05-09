#include <SDL.h>
#include <iostream>
#include <string>
#include "renderWindow.h"
#include "rect.h"
using namespace std;

renderWindow::renderWindow(const char* title, int w, int h) {
	window = nullptr;
	renderer = nullptr;
	window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if (window == nullptr)
		cout << "ERROR at SDL_CreateWindow(): " << SDL_GetError() << endl;
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
		cout << "ERROR at SDL_CreateRenderer(): " << SDL_GetError() << endl;

	running = true;
	fps = 60;
	startTick = SDL_GetTicks();
}
void renderWindow::setFPS(int newFPS) {
	startTick = SDL_GetTicks();
	fps = newFPS;
}
void renderWindow::clear() {
	Uint32 elapsedTicks = SDL_GetTicks() - startTick;
	if (1000 / fps > elapsedTicks)
		SDL_Delay(1000/fps - elapsedTicks);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
}
void renderWindow::display() {
	SDL_RenderPresent(renderer);
	startTick = SDL_GetTicks();
}

bool renderWindow::isOpen() {
	return running;
}
void renderWindow::close() {
	running = false;
}

void renderWindow::draw(const rect& obj) {
	SDL_SetRenderDrawColor(renderer, obj.rgba[0], obj.rgba[1], obj.rgba[2], obj.rgba[3]);
	SDL_RenderFillRect(renderer, &obj.box);
}
void renderWindow::setTitle(std::string title) {
	char* t = new char[title.size()+1];
	int i = 0;
	while (title[i] != 0) {
		t[i] = title[i];
		i++;
	}
	t[i] = 0;
	SDL_SetWindowTitle(window, t);
	delete[]t;
}

renderWindow::~renderWindow() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}