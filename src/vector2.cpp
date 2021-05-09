#include <iostream>

#include "vector2.h"
using namespace std;

vector2::vector2(int x, int y):x(x),y(y){
}
void vector2::move(vector2 obj) {
	x += obj.x;
	y += obj.y;
}
ostream& operator<<(ostream& out, const vector2& v2) {
	out << v2.x << ' ' << v2.y;
	return out;
}