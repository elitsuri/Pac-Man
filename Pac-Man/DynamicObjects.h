#pragma once
#include "Objects.h"
using namespace std;
using namespace sf;
enum directions_t
{
	right_t,
	down_t,
	left_t,
	up_t,
	stand_t,
};

class DynamicObjects : public Objects
{
public:
	DynamicObjects() {};
	~DynamicObjects() {};
	void add_speed(float to_add)
	{
		if (m_speed < 500)
			m_speed = m_speed + to_add;
	};
	void decrease_speed(float decrease)
	{
		if (m_speed > 100)
			m_speed = m_speed - decrease;
	};
	float get_speed(){ return m_speed; };
protected:
	float m_speed, change_pic, from_x ,from_y;
	virtual void define_color() = 0;
	directions_t m_direction;
	bool check_before_move(Vector2f center)
	{
		return ((abs(m_location.x - center.x) <= 3.f) && (abs(m_location.y - center.y) <= 3.f));
	};
};