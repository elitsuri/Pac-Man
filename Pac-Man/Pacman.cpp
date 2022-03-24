#include "Pacman.h"


/////////////////////////////// CONSTRUCTOR /////////////////////////////////
// build the pacman object by location and his icon.
Pacman::Pacman(sf::Vector2i location, char icon)
{
	m_location.x = (float)location.x * 30 + TO_CENTER; //update location.
	m_location.y = (float)location.y * 30 + TO_CENTER;

	sf::Texture* texture = Singleton::show().get_pic(0); //update picture.
	m_pic.setTexture(*texture);
	m_pic.setOrigin(TO_CENTER, TO_CENTER);
	m_icon = icon;
	define_color(); //define his color.
	m_speed = 150;
	from_x = 0;
	from_y = 0;
	m_direction = stand_t; //define his direction.
	change_pic = 0;
}

/////////////////////////////// DRAW /////////////////////////////////
// draw the pacman on the board.
void Pacman::draw(sf::RenderWindow & win, float clock_sample)
{
	float color;
	change_pic += clock_sample * m_speed;
	if (m_direction != stand_t)
		from_y = (float)m_direction * SHAPE;
	if (from_x == 0 && change_pic >= 15.f) //change between pictures.
	{
		from_x = 1;
		change_pic = 0;
	}

	else if (from_x == 1 && change_pic >= 15.f)
	{
		from_x = 0;
		change_pic = 0;
	}

	if (m_color == sf::Color::Red)
		color = 0;
	else if ((m_color == sf::Color::Blue))
		color = 60;
	else if ((m_color == sf::Color::Green))
		color = 120;

	m_pic.setTextureRect(sf::IntRect((int)0 + (int)from_x * SHAPE, (int)from_y, 30, 30));
	m_pic.setPosition(m_location.x + TO_CENTER, m_location.y + TO_CENTER);
	//m_pic.setColor(m_color);
	win.draw(m_pic);
}

/////////////////////////////// DEFINE COLOR /////////////////////////////////
// define color for pacman by icon.
void Pacman::define_color()
{
	if (m_icon == '@')
		m_color = sf::Color::Red;
	else if (m_icon == 'W')
		m_color = sf::Color::Green;
	else if (m_icon == 'S')
		m_color = sf::Color::Blue;
}

/////////////////////////////// MOVE /////////////////////////////////
// move the pacman.
void Pacman::move(float distance, directions_t dirc, sf::Vector2f center)
{
	if (check_before_move(center))
		m_direction = dirc;
	if (m_direction == up_t)
		m_location.y = m_location.y - distance;
	if (m_direction == down_t)
		m_location.y = m_location.y + distance;
	if (m_direction == right_t)
		m_location.x = m_location.x + distance;
	if (m_direction == left_t)
		m_location.x = m_location.x - distance;

}


/////////////////////////////// GET LOCATION /////////////////////////////////
// return the pacman location.
sf::Vector2f Pacman::get_location()
{
	return m_location;
}

/////////////////////////////// SET LOCATION /////////////////////////////////
// update the location to new place.
void Pacman::set_location(sf::Vector2f newp)
{
	m_location = newp;
}

/////////////////////////////// GET DIRECTION /////////////////////////////////
// return the direction.
directions_t Pacman::get_direction()
{
	return m_direction;
}

/////////////////////////////// SET SPEED /////////////////////////////////
// update the speed to new speed.
void Pacman::set_speed(float new_speed)
{

	m_speed = new_speed;
}




