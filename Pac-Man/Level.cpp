#include "Level.h"
#include "Wall.h"
#include "Cookie.h"


/////////////////////////////// = CONSTRUCTOR = ////////////////////////////////////
// build the level by the level number.
Level::Level(int level)
{
	m_level = level;
	m_deamons_sum = 0;

	ifstream file; //to read from file.
	char num = (char)(m_level)+'0';
	string end = ".txt";
	string file_name = "";
	file_name += num;
	file_name += end;
	file.open(file_name); //the name of the file.
	copy_to_file_vector(file); //copy to the file vector.
	make_m_board(); //do assign to the m_board.
	define_m_board(m_file_vector); //copy to the static vector.
}


/////////////////////////////// = DRAW FUNCTION = ///////////////////////////////////
//draw the static objects on the board.
void Level::draw(sf::RenderWindow & win, float clock_sample)
{
	for (int y = 0; y < m_length; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			if (m_board[y][x])	//if not null
				m_board[y][x]->draw(win, clock_sample);
		}
	}
}

/////////////////////////////// = GET PACMAN LOCATION = /////////////////////////////
//return the pacman location.
sf::Vector2i Level::get_pac_location()
{
	return pacman.location;
}

/////////////////////////////// = GET PACMAN ICON = /////////////////////////////////
//return the pacman icon.
char Level::get_pac_icon()
{
	return pacman.icon;
}

/////////////////////////////// = GET DEAMON = /////////////////////////////////
//return a struct of deamon locaion and his icon by the number.
struct keep_info Level::get_deamon(int deamon)
{
	return deamons[deamon];
}

/////////////////////////////// = GET DEAMON SUM= /////////////////////////////////
//return the total number of deamons.
int Level::get_deamons_sum()
{
	return m_deamons_sum;
}

/////////////////////////////// GET - WIDTH /////////////////////////////////
//return the width
int Level::get_width()
{
	return m_width;
}

/////////////////////////////// GET - LENGTH /////////////////////////////////
//return the lenth
int Level::get_length()
{
	return m_length;
}



/////////////////////////////// COPY - TO - FILE -VECTOR /////////////////////////////////
// copy the level string from file to the string vector.
void Level::copy_to_file_vector(ifstream &file)
{
	string line;
	file >> m_length >> m_width; //read width and length.
	getline(file, line); //eat enter;
	for (int index = 0; index < m_length; index++) // build the map
	{
		getline(file, line);
		m_file_vector.push_back(line);
	}
}

/////////////////////////////// DEFINE M BOARD /////////////////////////////////
// translate the static objects from location and icon (from the file vector) to 
//static objects . and keep ditails about pacman and deamons.
void Level::define_m_board(vector<string>m_file_vector)
{
	char icon;
	m_cookies = 0;
	sf::Vector2i location;

	for (int y = 0; y < m_length; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			location.x = x;
			location.y = y;

			icon = m_file_vector[y][x];

			switch (icon)
			{
				case '#':m_board[y][x] = make_unique <Wall>(sf::Color::Red, location, '#'); //red wall
					break;
				case 'E':m_board[y][x] = make_unique <Wall>(sf::Color::Green, location, 'E'); //green wall
					break;
				case 'D':m_board[y][x] = make_unique <Wall>(sf::Color::Blue, location, 'D'); //blue wall
					break;
				case '*':m_board[y][x] = make_unique <Cookie>(sf::Color::Red, location, '*');//red cookie
					m_cookies++;
					break;
				case 'I':m_board[y][x] = make_unique <Cookie>(sf::Color::Green, location, 'I'); //green cookie
					m_cookies++;
					break;
				case 'K':m_board[y][x] = make_unique <Cookie>(sf::Color::Blue, location, 'K'); //blue cookie
					m_cookies++;
					break;
				case '@':			//if pacman
				case 'W':
				case 'S':
				{
					pacman.icon = icon;
					pacman.location = location;
					break;
				}
				case '%':			//if deamon
				case 'T':
				case 'G':
				{
					struct keep_info deamon;
					deamon.icon = icon;
					deamon.location = location;
					deamons.push_back(deamon);
					m_deamons_sum++;
				}

			} //switch close
		}
	}
}

/////////////////////////////// MAKE M BOARD /////////////////////////////////
// build the m_board vector and define him to be nullptr in every cell.
void Level::make_m_board()
{
	m_board.resize(m_length);

	for (int i = 0; i < m_length; i++)
	{
		m_board[i].resize(m_width);
	}

	for (int i = 0; i < m_length; i++)
	{
		for (int j = 0; j < m_width; j++)
			m_board[i][j] = nullptr;
	}
}


/////////////////////////////// GET OBJECT /////////////////////////////////
// return pointer to static object from the static board by float location.
StaticObjects* Level::get_object(sf::Vector2f place)
{
	sf::Vector2i object;
	object.x = (int)place.x / SHAPE;
	object.y = (int)place.y / SHAPE;
	if (object.y >= m_length || object.x >= m_width)
		return nullptr;

	return m_board[object.y][object.x].get();

}

/////////////////////////////// COOKIE EATEN /////////////////////////////////
// when cookie has been eaten this funcion will update the sum of cookies on the board. 
void Level::cookie_eaten()
{
	m_cookies--;
}

/////////////////////////////// SET OBJECT NULL /////////////////////////////////
// release a uniqe ptr object on the board.
//we use this for eating cookies.
void Level::set_object_null(sf::Vector2f place)
{
	sf::Vector2i object;
	object.x = (int)place.x / SHAPE;
	object.y = (int)place.y / SHAPE;

	m_board[object.y][object.x] = nullptr;

}

/////////////////////////////// GET - COOKIES /////////////////////////////////
// return the number of cookies.
int Level::get_cookies()
{
	return m_cookies;
}

/////////////////////////////// SET - SPECIAL - COOKIE /////////////////////////////////
// set the new cookie on the static board. by location and icon.
void Level::set_special_cookie(int x, int y, char icon)
{
	sf::Vector2i location;
	location.x = x;
	location.y = y;
	switch (icon)
	{
		case 'B': m_board[y][x] = make_unique <Cookie>(sf::Color::Green, location, 'B');
			break;
		case 'V': m_board[y][x] = make_unique <Cookie>(sf::Color::Green, location, 'V');
			break;
		case 'H': m_board[y][x] = make_unique <Cookie>(sf::Color::Green, location, 'H');
			break;
	}
}


