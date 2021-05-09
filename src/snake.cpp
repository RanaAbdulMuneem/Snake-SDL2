#include <SDL.h>
#include <list>
#include <iterator>
#include <iostream>
#include <time.h>

#include "preprocessor.h"
#include "snake.h"
#include "rect.h"
#include "renderWindow.h"
#include "vector2.h"
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b; 
	b = temp;
}


snake::snake() {
	speed = 10;
	size = 10;
	restart();
	inputLock = false;
	morsel.setSize({ size,size });
	createMorsel();
}
void snake::restart() {
	gameOver = false;
	inputLock = false;
	direction = -1;
	prevDirection = -1;
	score = 0;

	body.clear();
	rect head;
	head.setSize({ size, 2*size });
	int x = 240;
	int y = 240;
	hitPoint.x = x + size/2;
	hitPoint.y = y;
	head.setPosition({ x, y });
	body.push_back(head);
	setColor(0, 255, 0, 0);
}

void snake::input(SDL_Event event) {
	if (!gameOver && inputLock)
		return;
	if (event.type == SDL_KEYDOWN) {
		if (direction == -1) {
			direction = 0;
			prevDirection = 0;
		}
		else {
			switch (event.key.keysym.sym) {
			case SDLK_UP:
				if (direction != 2) {
					prevDirection = direction;
					direction = 0;
				}
				break;
			case SDLK_RIGHT:
				if (direction != 3) {
					prevDirection = direction;
					direction = 1;
				}
				break;
			case SDLK_DOWN:
				if (direction != 0) {
					prevDirection = direction;
					direction = 2;
				}
				break;
			case SDLK_LEFT:
				if (direction != 1) {
					prevDirection = direction;
					direction = 3;
				}
				break;
			case SDLK_SPACE:
				restart();
				break;
			}
		}
		inputLock = true;
	}
}
bool snake::update() {
	if (!gameOver && direction != -1) {
		if (borderCollision() || selfCollision()) {
			setColor(255, 0, 0, 0);
			gameOver = true;
			return gameOver;
		}
		else {
			move();
			if (morselCollision()) {
				grow();
				createMorsel();
			}
		}
	}
	inputLock = false;
	return gameOver;
}

void snake::move() {
	if (direction == prevDirection) {
		moveForward();
	}
	else {
		switch (direction) {
		case 0:
			moveUp();
			break;
		case 1:
			moveRight();
			break;
		case 2:
			moveDown();
			break;
		case 3:
			moveLeft();
			break;
		}
		prevDirection = direction;
	}
	moveTail();
}
void snake::moveForward() {
	rect* head = &body.front();
	int headDir = segmentDirection(*head);
	switch (headDir) {
	case 0:
		head->moveY(-size);
		head->growH(size);
		hitPoint.move({0,-size});
		break;
	case 1:
		head->moveX(size);
		head->growW(-size);
		hitPoint.move({size,0});
		break;
	case 2:
		head->moveY(size);
		head->growH(-size);
		hitPoint.move({0,size});
		break;
	case 3:
		head->moveX(-size);
		head->growW(size);
		hitPoint.move({-size,0});
		break;
	}
}
void snake::moveUp() {
	rect* head = &body.front();
	int headDir = segmentDirection(*head);

	int x = head->getPosition().x;
	int y = head->getPosition().y;
	if (headDir == 1) {
		x -= size;
		y -= size;
	}
	else if (headDir == 3) {
		y -= 2*size;
	}
	int w = size;
	int h = 2*size;
	rect newHead(x, y, w, h);
	newHead.setColor(0, 255, 0, 0);
	body.push_front(newHead);
	hitPoint.x = newHead.getPosition().x + size / 2;
	hitPoint.y = newHead.getPosition().y;
}
void snake::moveRight() {
	rect* head = &body.front();
	int headDir = segmentDirection(*head);

	int x = head->getPosition().x;
	int y = head->getPosition().y;
	if (headDir == 0) {
		x += 2 * size;
	}
	else if (headDir == 2) {
		x += size;
		y -= size;
	}
	int w = -2 * size;
	int h = size;
	rect newHead(x, y, w, h);
	newHead.setColor(0,255,0,0);
	body.push_front(newHead);
	hitPoint.x = newHead.getPosition().x;
	hitPoint.y = newHead.getPosition().y + size/2;
}
void snake::moveDown() {
	rect* head = &body.front();
	int headDir = segmentDirection(*head);

	int x = head->getPosition().x;
	int y = head->getPosition().y;
	if (headDir == 1) {
		y += 2 * size;
	}
	else if (headDir == 3) {
		x += size;
		y += size;
	}
	int w = -size;
	int h = -2*size;
	rect newHead(x, y, w, h);
	newHead.setColor(0, 255, 0, 0);
	body.push_front(newHead);
	hitPoint.x = newHead.getPosition().x - size / 2;
	hitPoint.y = newHead.getPosition().y;
}
void snake::moveLeft() {
	rect* head = &body.front();
	int headDir = segmentDirection(*head);

	int x = head->getPosition().x;
	int y = head->getPosition().y;
	if (headDir == 0) {
		x -= size;
		y += size;
	}
	else if (headDir == 2) {
		x -= 2 * size;
	}
	int w = 2*size;
	int h = -size;
	rect newHead(x, y, w, h);
	newHead.setColor(0, 255, 0, 0);
	body.push_front(newHead);
	hitPoint.x = newHead.getPosition().x;
	hitPoint.y = newHead.getPosition().y - size/2;
}
void snake::moveTail() {
	rect* tail = &body.back();
	int tailDir = segmentDirection(*tail);
	switch (tailDir) {
	case 0:
		tail->growH(-size);
		break;
	case 1:
		tail->growW(size);
		break;
	case 2:
		tail->growH(size);
		break;
	case 3:
		tail->growW(-size);
		break;
	}
	int w = tail->getSize().x;
	int h = tail->getSize().y;
	if (abs(w) == abs(h))
		body.pop_back();
}
void snake::grow() {
	rect* tail = &body.back();
	int tailDir = segmentDirection(*tail);
	if (tailDir == 0) {
		tail->growH(size);
	}
	else if (tailDir == 1) {
		tail->growW(-size);
	}
	else if (tailDir == 2) {
		tail->growH(-size);
	}
	else if (tailDir == 3) {
		tail->growW(size);
	}
	score++;
}
void snake::createMorsel() {
	srand(time(nullptr));
	static int x = 1;
	static int y = 1;
	int tempx;
	int tempy;
	bool repeat = true;
	while (repeat) {
		repeat = false;
		x = ((x + 1) * rand()) % win_width;
		y = ((y + 1) * rand()) % win_height;

		tempx = (x / size) * size;
		tempy = (y / size) * size;
		if (tempx == 0)
			tempx += size;
		else if (tempx == win_width - size)
			tempx -= size;
		if (tempy == 0)
			tempy += size;
		else if (tempy == win_width - size)
			tempy -= size;

		list<rect>::iterator i = body.begin();
		for (i; i != body.end(); i++) {
			if (i->contains({ tempx,tempy })) {
				repeat = true;
				break;
			}
		}
	}
	morsel.setPosition({ tempx, tempy });
	morsel.setColor(255, 187, 0, 0);
}
//utility
int snake::segmentDirection(const rect& segment) {
	int w = segment.getSize().x;
	int h = segment.getSize().y;

	int segDir;
	if (abs(w) > abs(h)) {//segment is moving horizontally
		if (w < 0)
			return 1;
		else
			return 3;
	}
	else {				//segment is moving vertically
		if (h < 0)
			return 2;
		else
			return 0;
	}
}
bool snake::borderCollision() {
	int x = body.front().getPosition().x;
	int y = body.front().getPosition().y;

	if (direction == 0 && y == 0)//top collision
		return true;
	else if (direction == 1 && x == win_width)//right collision
		return true;
	else if (direction == 2 && y == win_height)//left collision
		return true;
	else if (direction == 3 && x == 0)//bottom collision
		return true;

	return false;
}
bool snake::selfCollision() {
	if (body.size() > 1) {
		list<rect>::iterator i = body.begin();
		i++;
		for (i; i != body.end(); i++) {
			if (i->contains(hitPoint))
				return true;
		}
	}
	return false;
}
bool snake::morselCollision() {
	return morsel.contains(hitPoint);
}
void snake::setColor(int r, int g, int b, int a) {
	list<rect>::iterator i = body.begin();
	for (i; i != body.end(); i++) {
		i->setColor(r, g, b, a);
	}
}
void snake::drawTo(renderWindow& window) {
	list<rect>::iterator i = body.begin();
	for (i; i != body.end(); i++) {
		window.draw(*i);
	}
	if (direction != -1)
		window.draw(morsel);
}
int snake::getScore() {
	return score;
}
snake::~snake() {

}

