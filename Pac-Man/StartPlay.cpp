#include "StartPlay.h"
/////////////////////////////// CONSTRUCTOR /////////////////////////////////
// will build the menu of the game.
StartPlay::StartPlay()
{
	sf::Font font;
	m_vector_but.push_back(std::make_unique<StartButton>()); //create start button
	m_vector_but.push_back(std::make_unique<HelpButton>());	//create help button
	m_vector_but.push_back(std::make_unique<ExitButton>()); //create exit button

	m_back.setTexture(*(Singleton::show().get_pic(6)));
	m_back.setTextureRect(sf::IntRect(0, 0, 900, 700));
}

/////////////////////////////// RUN /////////////////////////////////
// the main funcion of the menu.
// she will run until one of the buttons is pressed.
void StartPlay::run(bool &exit_on)
{
	sf::Event event;
	sf::Vector2f mouseCoords;
	sf::RenderWindow window(sf::VideoMode(900, 700, 32), "Pac-Man", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(500, 100));
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed: //check if the X is pressed.
				{
					exit_on = false;
					window.close();
					break;
				}
				case sf::Event::MouseButtonPressed: //check if button is pressed
				{
					mouseCoords.x = (float)event.mouseButton.x;
					mouseCoords.y = (float)event.mouseButton.y;
					for (size_t i = 0; i < m_vector_but.size(); ++i)
						m_vector_but[i]->ClickOn(mouseCoords, window, exit_on);
				}
				case sf::Event::MouseMoved: //check if the mouse moved on the buttons.
				{
					mouseCoords = window.mapPixelToCoords({ event.mouseMove.x,event.mouseMove.y });
					for (size_t i = 0; i < m_vector_but.size(); ++i)
						m_vector_but[i]->moveOn(mouseCoords);
					break;
				}
				default:
					break;
			}
		}
		window.clear();
		window.draw(m_back);
		for (size_t i = 0; i < m_vector_but.size(); ++i)
			m_vector_but[i]->draw(window);
		window.display();
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			exit_on = false;
			window.close();
			break;
		}
	}
}

StartPlay::~StartPlay()
{
}