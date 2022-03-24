#include "Cookie.h"

Cookie::Cookie(Color color, Vector2i location, char icon) 
{
	Texture* texture;
	if (icon == 'V' || icon == 'B' || icon == 'H') 
	{
		switch (icon)
		{
			case 'V':
				texture = Singleton::show().get_pic(7);
			break;
			case 'B':
				texture = Singleton::show().get_pic(8);
				break;
			case 'H':
				texture = Singleton::show().get_pic(9);
				break;
		}
	}
	else 
		texture = Singleton::show().get_pic(2);
	m_pic.setTexture(*texture); 
	m_pic.setOrigin(TO_CENTER, TO_CENTER);
	m_icon = icon; 
	m_color = color;
	m_location.x = (float)location.x * 30 + TO_CENTER; 
	m_location.y = (float)location.y * 30 + TO_CENTER;
}

void Cookie::draw(RenderWindow &win, float clock_sample)
{
	m_pic.setTextureRect(IntRect(0, 0, 30, 30));
	m_pic.setPosition(m_location.x + TO_CENTER, m_location.y + TO_CENTER);
	if(m_icon != 'V' && m_icon != 'B' && m_icon != 'H')
		m_pic.setColor(m_color);
	win.draw(m_pic);
}