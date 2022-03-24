#include "ExitButton.h"



/////////////////////// CONSTRUCTOR //////////////////////////////////
ExitButton::ExitButton()
{
	m_sprite.setTexture(*m_text); //set the first pic
	m_sprite.setTextureRect(sf::IntRect(317,507, 300, 75));
	m_sprite.setPosition(300, 530);
	m_sprite.setColor(sf::Color(sf::Color::Cyan));
	m_button_on.setTexture(*m_text); //set the second pic.
	m_button_on.setTextureRect(sf::IntRect(322,585, 300, 75));
	m_button_on.setPosition(300,530);
	m_button_before = m_sprite;
}


/////////////////////// CLICK ON //////////////////////////////////
//define whats happened when the user click on exit in the menu.
void ExitButton::ClickOn(sf::Vector2f pos,sf::RenderWindow & window,bool & exit_on)
{
	if (!m_sprite.getGlobalBounds().contains(pos))
		return;
	exit_on = false; //update the exit on boolian (do not open the menu again).
	window.close();
}

/////////////////////// MOVE ON //////////////////////////////////
//define whats happened when the user move on the exit in the menu.
void ExitButton::moveOn(sf::Vector2f pos)
{
	if (m_sprite.getGlobalBounds().contains(pos))
		m_sprite = m_button_on; //switch between the pictures.
	else
		m_sprite = m_button_before;
}

/////////////////////// DRAW //////////////////////////////////
//draw the button.
void ExitButton::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

ExitButton::~ExitButton()
{}