#pragma once
#include "StaticObjects.h"
using namespace std;
using namespace sf;
class Cookie : public StaticObjects
{
public:
	Cookie(Color color, Vector2i location, char icon);
	void draw(RenderWindow &win, float clock_sample);
};