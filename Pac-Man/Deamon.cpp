#include "Deamon.h"


Deamon::Deamon(Vector2i location, char icon)
{
	m_location.x = (float)location.x * 30 + TO_CENTER;
	m_location.y = (float)location.y * 30 + TO_CENTER;

	Texture* texture = Singleton::show().get_pic(1); 
	m_pic.setTexture(*texture);
	m_pic.setOrigin(TO_CENTER, TO_CENTER);
	m_icon = icon; 
	define_color();
	m_speed = 150;
	from_y = 0;
	from_x = 0;
	change_pic = 0;
	m_direction = stand_t; 
	m_time_counter = 0;
}

void Deamon::draw(RenderWindow & win, float clock_sample)
{
	float color;
	change_pic += clock_sample * m_speed;
	if (m_direction != stand_t)
		from_y = (float)m_direction * SHAPE;
	if (from_x == 0 && change_pic >= 15.f)
	{
		from_x = 1;
		change_pic = 0;
	}
	else if (from_x == 1 && change_pic >= 15.f)
	{
		from_x = 0;
		change_pic = 0;
	}
	if (m_color == Color::Red)
		color = 0;
	else if ((m_color == Color::Blue))
		color = 60;
	else if ((m_color == Color::Green))
		color = 120;

	m_pic.setTextureRect(IntRect((color + from_x * SHAPE), from_y, 30, 30));
	m_pic.setPosition(m_location.x + TO_CENTER, m_location.y + TO_CENTER);
	win.draw(m_pic);
}

void Deamon::move(Vector2f center, float clock_sample, Vector2f pac)
{
	float distance = clock_sample * m_speed;

	int current = (int)m_direction;
	int num = current;
	directions_t dirc = stand_t;

	if (m_icon != '%') 
	{
		while (current == num)
		{
			num = rand() % 4;
			switch (num)
			{
			case 0:
				dirc = up_t;
				break;
			case 1:
				dirc = down_t;
				break;
			case 2:
				dirc = left_t;
				break;
			case 3:
				dirc = right_t;
			}
		}
		if (check_before_move(center) && m_time_counter >= 1.f)
		{
			m_direction = dirc;
			m_time_counter = 0;
		}
	}

	else 
	{
		num = rand() % 2;
		if (num % 2 == 0)
		{
			if (pac.x > m_location.x)
				dirc = right_t;
			if (pac.x < m_location.x)
				dirc = left_t;
			if (pac.x == m_location.x)
			{
				if (pac.y > m_location.y)
					dirc = down_t;
				if (pac.y < m_location.y)
					dirc = up_t;
			}
		}
		else
		{
			if (pac.y > m_location.y)
				dirc = down_t;
			if (pac.y < m_location.y)
				dirc = up_t;
			if (pac.y == m_location.y)
			{
				if (pac.x > m_location.x)
					dirc = right_t;
				if (pac.x < m_location.x)
					dirc = left_t;
			}
		}
		if (check_before_move(center))
		{
			m_direction = dirc;
			m_time_counter = 0;
		}
	}
	if (m_direction == up_t)
		m_location.y = m_location.y - distance;
	if (m_direction == down_t)
		m_location.y = m_location.y + distance;
	if (m_direction == right_t)
		m_location.x = m_location.x + distance;
	if (m_direction == left_t)
		m_location.x = m_location.x - distance;
}

void Deamon::update_time_counter(float add)
{
	m_time_counter += add;
}

Vector2f Deamon::get_location()
{
	return m_location;
}

void Deamon::set_location(Vector2f location)
{
	m_location = location;
}

void Deamon::set_speed(float new_speed)
{
	m_speed = new_speed;
}

void Deamon::set_direction(directions_t dirc)
{
	m_direction = dirc;
}

directions_t Deamon::get_direction()
{
	return m_direction;
}

void Deamon::define_color()
{
	if (m_icon == '%')
		m_color = Color::Red;
	else if (m_icon == 'T')
		m_color = Color::Green;
	else if (m_icon == 'G')
		m_color = Color::Blue;
}