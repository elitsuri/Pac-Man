#pragma once
#include "StaticObjects.h"
using namespace std;
using namespace sf;
class Wall : public StaticObjects
{

public:
	Wall(Color color, Vector2i location, char icon);
	void draw(RenderWindow &win,float clock_sample);
};