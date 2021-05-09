#pragma once
#include <iostream>
using namespace std;

class vector2{
public:
	int x;
	int y;

	vector2(int x=0, int y=0);
	void move(vector2 obj);
	friend ostream& operator<<(ostream& out,const vector2& v2);
};