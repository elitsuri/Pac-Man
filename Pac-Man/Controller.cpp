#include "Controller.h"

Controller::Controller()
{
	m_deamons_sum = 0;
	m_lives = 3;
	m_cookie_clock = 0;
	m_background.openFromFile("sound/music.ogg");
	m_good_luck.openFromFile("sound/goodluck.ogg");
	m_eating.openFromFile("sound/eating.ogg");
	m_eating.setVolume(50);
	m_game_over.openFromFile("sound/Game Over.ogg");
	m_lost.openFromFile("sound/lost.ogg");
	m_level_end.openFromFile("sound/level_end.ogg");
	m_special_cookie.openFromFile("sound/cookie.ogg");
	m_bad_cookie.openFromFile("sound/bad_cookie.ogg");
	m_points = 0;
	m_sound_switch = true;
	special_cookie_loc = { -1,-1 };
}

void Controller::run()
{
	srand(unsigned(time(NULL)));
	Event event;
	Clock clock;
	directions_t side = stand_t;
	Texture* back;
	Vector2i pos;
	pos.x = 750;
	pos.y = 200;

	for (int level_num = 1; level_num <= 5; level_num++)
	{
		m_background.play();
		RenderWindow window(VideoMode(900, 700, 32), "Pac-Man", Style::Titlebar | Style::Close);
		back = Singleton::show().get_pic(14);
		background.setTexture(*back);
		window.setPosition(Vector2i(500, 100));
		Level level(level_num);
		m_cookies_sum = level.get_cookies();
		side = stand_t;
		m_deamons_sum = level.get_deamons_sum();
		deamons_vec_build(level);
		create_deamons();
		float clock_sample = 0;
		bool bad = false;
		bool good = false;
		bool health = false;
		bool skip = true;
		m_special_cookie_counter = 0;
		m_cookie_clock = 0;
		special_cookie_loc = { -1,-1 };
		pacman = make_unique <Pacman>(level.get_pac_location(), level.get_pac_icon());
		GameTime menu(level_num, pacman.get()->get_speed(), m_lives, 0);
		set_speed_by_level((float)m_cookies_sum);

		while (window.isOpen())
		{
			while (window.pollEvent(event))
			{
				clock.restart();
				if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				{
					game_over(window);
					return;
				}
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Up)
						side = up_t;
					if (event.key.code == Keyboard::Down)
						side = down_t;
					if (event.key.code == Keyboard::Left)
						side = left_t;
					if (event.key.code == Keyboard::Right)
						side = right_t;
					if (event.key.code == Keyboard::Space)
						side = stand_t;
					if (event.key.code == Keyboard::S)
						sound_switch();
					if (event.key.code == Keyboard::L)
					{
						set_next_level(window);
						skip = false;
					}
				}
			}
			if (skip)
			{
				clock_sample = clock.getElapsedTime().asSeconds();
				move(level.get_width(), level.get_length(), side, clock_sample, level,
					distance(clock_sample), good, bad, menu, window);
				draw(window, level, clock_sample, menu);
				special_cookie(good, bad, health, clock_sample, level);
				clock.restart();
				window.display();
				cookie_status(good, bad, health, clock_sample, level, menu);
			}
			if (m_lives == 0)
			{
				game_over(window);
				return;
			}
			if (level.get_cookies() == 0)
				set_next_level(window);
		}
	}
}

void Controller::start_over(Level& level)
{
	Vector2f pac_loc;
	pac_loc.x = (float)level.get_pac_location().x * SHAPE + 15;
	pac_loc.y = (float)level.get_pac_location().y * SHAPE + 15;

	pacman.get()->set_location(pac_loc);
	recreate_deamons();
}

void Controller::set_speed_by_level(float cookie_sum)
{
	if (cookie_sum <= 100)
	{
		pacman.get()->set_speed(225);
		for (int i = 0; i < m_deamons_sum; i++)
			m_deamons[i].set_speed(150);
	}
	else
	{
		pacman.get()->set_speed(225);
		for (int i = 0; i < m_deamons_sum; i++)
			m_deamons[i].set_speed(150);
	}
}

void Controller::cookie_status(bool& good, bool& bad, bool& health, float clock_sample, Level& level, GameTime& menu)
{
	m_cookie_clock += clock_sample;
	if (good && m_cookie_clock >= 4.f)
	{
		good = false;
		m_cookie_clock = 0;
		set_speed_by_level((float)m_cookies_sum);
		menu.set_speed(pacman.get()->get_speed());
		level.set_object_null(special_cookie_loc);
		special_cookie_loc = { -1,-1 };
	}
	if (bad && m_cookie_clock >= 4.f)
	{
		bad = false;
		m_cookie_clock = 0;
		set_speed_by_level((float)m_cookies_sum);
		level.set_object_null(special_cookie_loc);
		special_cookie_loc = { -1,-1 };
	}
	if (health && m_cookie_clock >= 4.f)
	{
		health = false;
		m_cookie_clock = 0;
		level.set_object_null(special_cookie_loc);
		special_cookie_loc = { -1,-1 };
	}
}

void Controller::game_over(RenderWindow& window)
{
	Texture* end;
	Sprite f_end;
	Vector2f position;
	position.x = 0;
	position.y = 0;
	end = (Singleton::show().get_pic(10));
	f_end.setTexture(*end);
	f_end.setTextureRect(IntRect(0, 0, 900, 700));
	m_background.stop();
	window.clear();
	f_end.setPosition(0, 10);
	window.draw(f_end);
	window.display();
	m_game_over.play();
	Sleep(4000);
	window.close();
}

void Controller::set_next_level(RenderWindow& window)
{
	m_background.stop();
	m_level_end.play();
	Texture* trophy = Singleton::show().get_pic(11);
	Sprite tropy;
	tropy.setTexture(*trophy);
	tropy.setTextureRect(IntRect(0, 0, 900, 700));
	window.draw(tropy);
	window.display();
	Sleep(3000);
	window.close();
	for (int i = 0; i < m_deamons_sum; i++)
	{
		m_deamons.pop_back();
		deamons.pop_back();
	}
	m_points = 0;
}

void Controller::sound_switch()
{
	if (m_sound_switch)
	{
		m_background.setVolume(0);
		m_game_over.setVolume(0);
		m_eating.setVolume(0);
		m_lost.setVolume(0);
		m_level_end.setVolume(0);
		m_special_cookie.setVolume(0);
		m_bad_cookie.setVolume(0);
		m_sound_switch = false;
	}
	else
	{
		m_background.setVolume(100);
		m_game_over.setVolume(100);
		m_eating.setVolume(50);
		m_lost.setVolume(100);
		m_level_end.setVolume(100);
		m_special_cookie.setVolume(100);
		m_bad_cookie.setVolume(100);
		m_sound_switch = true;
	}
}

void Controller::special_cookie(bool& good, bool& bad, bool& health, float clock_sample, Level& level)
{
	int x; int y;
	char icon{};
	Vector2f location = { 45,45 };
	m_special_cookie_counter += clock_sample;

	if (m_special_cookie_counter >= 5 && special_cookie_loc.x == -1 && special_cookie_loc.y == -1)
	{
		x = rand() % level.get_width();
		y = rand() % level.get_length();
		location.x = (float)x * SHAPE + 15;
		location.y = (float)y * SHAPE + 15;

		while (level.get_object(location) != nullptr)
		{
			x = rand() % level.get_width();
			y = rand() % level.get_length();
			location.x = (float)x * SHAPE + 15;
			location.y = (float)y * SHAPE + 15;
		}
		if (x % 3 == 0)
		{
			icon = 'V';
			good = true;
			m_cookie_clock = 0;
		}
		else if (x % 3 == 1)
		{
			icon = 'B';
			bad = true;
			m_cookie_clock = 0;
		}
		else if (x % 3 == 2)
		{
			icon = 'H';
			health = true;
			m_cookie_clock = 0;
		}
		level.set_special_cookie(x, y, icon);
		m_special_cookie_counter = 0;
		special_cookie_loc = location;
	}
}

void Controller::deamons_vec_build(Level& level)
{
	for (int index = 0; index < m_deamons_sum; index++)
	{
		struct keep_info deamon;
		deamon = level.get_deamon(index);
		deamons.push_back(deamon);
	}
}

void Controller::deamons_draw(RenderWindow& win, float clock_sample)
{
	for (int index = 0; index < m_deamons_sum; index++)
		m_deamons[index].draw(win, clock_sample);
}

float Controller::distance(float clock_sample)
{
	float distance = clock_sample * pacman.get()->get_speed();
	return distance;
}

void Controller::draw(RenderWindow& win, Level& level, float clock_sample, GameTime& menu)
{
	win.clear();
	win.draw(background);
	level.draw(win, clock_sample);

	for (int deamon = 0; deamon < m_deamons_sum; deamon++)
		m_deamons[deamon].draw(win, clock_sample);

	pacman.get()->draw(win, clock_sample);
	menu.draw(win);
}


Vector2f Controller::pacman_get_center(int width, int length)
{
	int i, y;
	Vector2f location;
	location = pacman.get()->get_location();

	i = (int)location.x / SHAPE;
	y = (int)location.y / SHAPE;
	i = i * SHAPE + 15;
	y = y * SHAPE + 15;
	location.x = (float)i;
	location.y = (float)y;

	return location;
}


Vector2f Controller::deamon_get_center(Deamon deamon, int width, int length)
{
	int i, y;
	Vector2f location;
	location = deamon.get_location();

	i = (int)location.x / SHAPE;
	y = (int)location.y / SHAPE;
	i = i * SHAPE;
	y = y * SHAPE;
	location.x = (float)i + 15;
	location.y = (float)y + 15;

	return location;
}

void Controller::move(int width, int length, directions_t side, float clock_sample, Level& level,
					float distance, bool& good, bool& bad, GameTime& menu, RenderWindow& window)
{
	Vector2f pac_center; 
	Vector2f pac_prev = pacman.get()->get_location();	
	Vector2f deamon_prev;
	pac_center = pacman_get_center(width, length);	
	pacman->move(distance, side, pac_center);	
	check_pacman_bounds(width, length);
	pacman_colide_check(pac_prev, level, width, length, good, bad, menu, window);
	menu.set_speed(pacman.get()->get_speed());

	for (int deamon = 0; deamon < m_deamons_sum; deamon++) 
	{
		m_deamons[deamon].update_time_counter(clock_sample);
		deamon_prev = m_deamons[deamon].get_location(); 
		m_deamons[deamon].move(deamon_get_center(m_deamons[deamon], width, length), clock_sample, pacman.get()->get_location());
		check_deamon_bounds(m_deamons[deamon], width, length);	
		deamons_colide_check(m_deamons[deamon], deamon_prev, level, width, length);
	}
}

void Controller::create_deamons()
{
	for (int i = 0; i < m_deamons_sum; i++)
		m_deamons.push_back(Deamon(deamons[i].location, deamons[i].icon));
}

void Controller::check_deamon_bounds(Deamon& deamon, int width, int length)
{
	Vector2f temp;
	float n_width = (float)width * SHAPE;
	float n_length = (float)length * SHAPE;

	if (deamon.get_location().x > n_width - 1)
	{
		temp.x = 0;
		temp.y = deamon.get_location().y;
		deamon.set_location(temp);
	}
	if (deamon.get_location().x < 0)
	{
		temp.x = n_width - 1;
		temp.y = deamon.get_location().y;
		deamon.set_location(temp);
	}
	if (deamon.get_location().y > n_length - 1)
	{
		temp.y = 0;
		temp.x = deamon.get_location().x;
		deamon.set_location(temp);

	}
	if (deamon.get_location().y < 0)
	{
		temp.y = n_length - 1;
		temp.x = deamon.get_location().x;
		deamon.set_location(temp);
	}
}

void Controller::check_pacman_bounds(int width, int length)
{
	Vector2f temp;
	float n_width = (float)width * SHAPE;
	float n_length = (float)length * SHAPE;

	if (pacman.get()->get_location().x > n_width - 1)
	{
		temp.x = 1;
		temp.y = pacman.get()->get_location().y;
		pacman.get()->set_location(temp);
	}
	if (pacman.get()->get_location().x < 0)
	{
		temp.x = n_width - 1;
		temp.y = pacman.get()->get_location().y;
		pacman.get()->set_location(temp);
	}
	if (pacman.get()->get_location().y > n_length - 1)
	{
		temp.y = 0;
		temp.x = pacman.get()->get_location().x;
		pacman.get()->set_location(temp);
	}
	if (pacman.get()->get_location().y < 0)
	{
		temp.y = n_length - 1;
		temp.x = pacman.get()->get_location().x;
		pacman.get()->set_location(temp);
	}
}

void Controller::pacman_colide_check(Vector2f prev, Level& level, int width, int length, bool& good,
	bool& bad, GameTime& menu,RenderWindow& window)
{
	Vector2i temp;
	Vector2f pac_fix = prev;
	StaticObjects* obj;
	directions_t dirc_t = pacman.get()->get_direction();

	if (dirc_t == up_t)
		pac_fix.y = pac_fix.y - 15;
	if (dirc_t == down_t)
		pac_fix.y = pac_fix.y + 15;
	if (dirc_t == left_t)
		pac_fix.x = pac_fix.x - 15;
	if (dirc_t == right_t)
		pac_fix.x = pac_fix.x + 15;
	temp.x = (int)pac_fix.x / SHAPE;
	temp.y = (int)pac_fix.y / SHAPE;
	pac_fix.x = (float)temp.x * SHAPE + 15;
	pac_fix.y = (float)temp.y * SHAPE + 15;

	if (dirc_t != stand_t)
	{
		obj = level.get_object(pac_fix); 
		if (obj != nullptr)
		{
			if (typeid(*obj) == typeid(Wall)) 
				pacman.get()->set_location(prev);
			else if (typeid(*obj) == typeid(Cookie)) 
			{
				m_eating.play();
				m_points += 2 * (m_deamons_sum + 1);
				menu.set_points(m_points);
				switch (obj->get_icon()) 
				{
				case 'V':
					pacman.get()->add_speed(100);
					good = true;
					m_special_cookie.play();
					break;
				case 'B':
					pacman.get()->decrease_speed(100);
					bad = true;
					m_bad_cookie.play();
					break;
				case 'H':
					m_lives++;
					menu.set_lives(m_lives);
					m_bad_cookie.play();
					break;
				case '*':
				case 'I':
				case 'K':
					level.cookie_eaten();
					break;
				}
				level.set_object_null(pac_fix);
			}
		}
	}
	for (int deamon = 0; deamon < m_deamons_sum; deamon++) 
	{
		if ((abs(pacman.get()->get_location().x - m_deamons[deamon].get_location().x) <= 15.f)
			&& (abs(pacman.get()->get_location().y - m_deamons[deamon].get_location().y) <= 15.f))
		{
			m_lives--; 
			Texture* lost = Singleton::show().get_pic(12); 
			Sprite tropy;
			tropy.setTexture(*lost);
			tropy.setTextureRect(IntRect(0, 0, 890, 890));
			tropy.setPosition(0, -100);
			window.draw(tropy);
			window.display(); 
			m_background.pause();
			m_lost.play(); 
			Sleep(2000);
			menu.set_lives(m_lives); 
			start_over(level); 
			m_background.play();
		}
	}
}

void Controller::deamons_colide_check(Deamon& deamon, Vector2f prev, Level& level, int width, int length)
{
	Vector2f deamon_fix = prev;
	StaticObjects* obj;
	directions_t dirc_t = deamon.get_direction();
	Vector2i temp;

	if (dirc_t == up_t)
		deamon_fix.y = deamon_fix.y - 15;
	if (dirc_t == down_t)
		deamon_fix.y = deamon_fix.y + 15;
	if (dirc_t == left_t)
		deamon_fix.x = deamon_fix.x - 15;
	if (dirc_t == right_t)
		deamon_fix.x = deamon_fix.x + 15;
	temp.x = (int)deamon_fix.x / SHAPE;
	temp.y = (int)deamon_fix.y / SHAPE;
	deamon_fix.x = (float)temp.x * SHAPE + 15;
	deamon_fix.y = (float)temp.y * SHAPE + 15;

	if (dirc_t != stand_t)
	{
		obj = level.get_object(deamon_fix);
		if (obj != nullptr)
		{
			if (typeid(*obj) == typeid(Wall))
			{
				deamon.set_location(prev);
				int current = (int)dirc_t;
				int num = current;
				directions_t dirc = stand_t;
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
				deamon.set_direction(dirc);
			}
		}
	}
}

void Controller::recreate_deamons()
{
	for (int i = 0; i < m_deamons_sum; i++)
	{
		Vector2f temp;
		temp.x = (float)deamons[i].location.x * SHAPE + 15;
		temp.y = (float)deamons[i].location.y * SHAPE + 15;
		m_deamons[i].set_location(temp);
	}
}