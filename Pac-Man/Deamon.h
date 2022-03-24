#pragma once
#include "DynamicObjects.h"
using namespace std;
using namespace sf;

class Deamon :public DynamicObjects
{
public:
	Deamon(Vector2i location, char icon);
	void draw(RenderWindow &window,float clock_sample);
	void move(Vector2f center, float clock_sample, Vector2f pac);
	void update_time_counter(float add);
	Vector2f get_location();
	void set_location(Vector2f location);
	void set_speed(float new_speed);
	void set_direction(directions_t dirc);
	directions_t get_direction();
private:
	void define_color();
	float m_time_counter;
};