#include <SDL.h>
#include "rect.h"
#include "vector2.h"

rect::rect() {
	box.x = box.y = 0;
	box.w = box.h = 0;
	for (int i = 0; i < 4; i++)
		rgba[0] = 0;
}
rect::rect(int x, int y, int w, int h) {
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	for (int i = 0; i < 4; i++)
		rgba[i] = 0;
}
rect::rect(const rect& obj) {
	box = obj.box;
	for (int i = 0; i < 4; i++)
		rgba[i] = obj.rgba[i];
}

void rect::setX(int x) {
	box.x = x;
}
void rect::setY(int y) {
	box.y = y;
}
void rect::setW(int w) {
	box.w = w;
}
void rect::setH(int h) {
	box.h = h;
}
void rect::setPosition(vector2 pos) {
	setX(pos.x);
	setY(pos.y);
}
void rect::setSize(vector2 size) {
	setW(size.x);
	setH(size.y);
}

vector2 rect::getPosition() {
	return {box.x, box.y};
}
vector2 rect::getSize() const {
	return { box.w, box.h };
}

void rect::moveX(int x) {
	box.x += x;
}
void rect::moveY(int y) {
	box.y += y;
}
void rect::growW(int w) {
	box.w += w;
}
void rect::growH(int h) {
	box.h += h;
}
void rect::move(vector2 pos) {
	moveX(pos.x);
	moveY(pos.y);
}
void rect::grow(vector2 size) {
	growW(size.x);
	growH(size.y);
}

bool rect::contains(const vector2& point) {
	int x1 = box.x;
	int x2 = x1 + box.w;
	int y1 = box.y;
	int y2 = y1 + box.h;

	if (x1 > x2)
		swap(x1, x2);
	if (y1 > y2)
		swap(y1, y2);

	if (point.x >= x1 && point.x <= x2)
		if (point.y >= y1 && point.y <= y2)
			return true;
	return false;
}

void rect::setColor(int r, int g, int b, int a) {
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
}