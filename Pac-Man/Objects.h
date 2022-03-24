#pragma once
#include <SFML\Graphics.hpp>
#include "Singleton.h"
using namespace std;
using namespace sf;
const float HEIGHT = 30;
const float WIDTH = 30;
const float TO_CENTER = 15;
const int SHAPE = 30;

class Objects
{
public:
	Objects();
	~Objects();
	virtual void draw(RenderWindow & win,float clock_sample) = 0;
	char get_icon();
protected:
	char m_icon;
	Sprite m_pic;
	Color m_color;
	Vector2f m_location;
};