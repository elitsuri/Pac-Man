#include "Wall.h"

/////////////////////// CONSTRUCTOR //////////////////////////////////
//will get the color , location , the icon and will create a wall (almost like cookie).
Wall::Wall(sf::Color color, sf::Vector2i location , char icon)
{
	sf::Texture* texture = Singleton::show().get_pic(3);
	m_pic.setTexture(*texture);
	m_pic.setOrigin(TO_CENTER, TO_CENTER);

	m_icon = icon;
	m_color = color;
	m_location.x = (float)location.x * 30 + TO_CENTER;
	m_location.y = (float)location.y * 30 + TO_CENTER;
	
}

/////////////////////// DRAW //////////////////////////////////
//the draw funtion for wall(almost like cookie).
void Wall::draw(sf::RenderWindow & win,float clock_sample)
{
	m_pic.setTextureRect(sf::IntRect(0, 0, 30, 30));
	m_pic.setPosition(m_location.x + TO_CENTER, m_location.y + TO_CENTER);
	m_pic.setColor(m_color);
	win.draw(m_pic);
}
