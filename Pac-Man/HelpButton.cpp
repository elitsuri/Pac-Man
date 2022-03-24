#include "HelpButton.h"

/////////////////////// CONSTRUCTOR //////////////////////////////////
//build the help button.
HelpButton::HelpButton()
{
	m_sprite.setTexture(*m_text); //set the first pic
	m_sprite.setTextureRect(sf::IntRect (333,330, 510, 75));
	m_sprite.setPosition(300,440);
	m_button_on.setTexture(*m_text); //set the second pic
	m_button_on.setTextureRect(sf::IntRect(322,409, 510, 75));
	m_button_on.setPosition(300,440);
	m_button_before = m_sprite;
	m_button_help = false;
}

/////////////////////// CLICK ON //////////////////////////////////
//define whats happened when the user click on exit in the menu.
void HelpButton::ClickOn(sf::Vector2f pos, sf::RenderWindow & window,bool & exit_on)
{
	sf::Sprite helpS;
	sf::Texture *helpT;
	if (!m_sprite.getGlobalBounds().contains(pos))
		return;
	helpT = Singleton::show().get_pic(13); //load the help pic from the singleton.
	helpS.setTexture(*helpT);
	window.clear();
	window.draw(helpS); //show the help screen.
	window.display();
	sf::Vector2f mouseCoords;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				//case sf::Event::Closed:
			//	case sf::Event::KeyPressed:
				case sf::Event::MouseButtonPressed:
					return;			
			}
		}
	}
}

/////////////////////// MOVE ON //////////////////////////////////
//define whats happened when the user move on exit in the menu.
void HelpButton::moveOn(sf::Vector2f pos)
{
	if (m_sprite.getGlobalBounds().contains(pos))
		m_sprite = m_button_on;
	else
		m_sprite = m_button_before;
}




/////////////////////// DRAW //////////////////////////////////
//print the button.
void HelpButton::draw(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}

HelpButton::~HelpButton()
{}
