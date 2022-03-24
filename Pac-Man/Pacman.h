#pragma once
#include "DynamicObjects.h"
using namespace std;
using namespace sf;
class Pacman : public DynamicObjects
{
public:
	Pacman(Vector2i location, char icon);
	void draw(RenderWindow &win, float clock_sample);
	void move(float distance, directions_t dirc, Vector2f center);
	Vector2f get_location();
	void set_location(Vector2f newp);
	directions_t get_direction();
	void set_speed(float new_speed);
private:
	void define_color();

};