#include <SDL.h>
#include <iostream>

#include "preprocessor.h"
#include "renderWindow.h"
#include "snake.h"
using namespace std;

int main(int argc, char* arg[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "ERROR at SDL_INIT: " << SDL_GetError() << endl;

	renderWindow window("WIP", win_width, win_height);
	SDL_Event event;

	snake snake;
	int points = snake.getScore();
	char title[50];
	string score;


	Uint32 blockStart;
	Uint32 blockTime = 2000;

	window.setFPS(25);
	while (window.isOpen()) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				window.close();
			}
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					window.close();
					break;
				}
			}
			snake.input(event);
		}
		snake.update();

		points = snake.getScore();
		score = "Score: " + to_string(points);
		window.setTitle(score);
		
		window.clear();
		snake.drawTo(window);
		window.display();
	}

	SDL_Quit();
	return 0;
}