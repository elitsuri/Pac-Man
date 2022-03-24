#include "GameTime.h"

GameTime::GameTime(int level, float speed, int lives, int points)
{
	m_level = level; 
	m_speed = speed;
	m_lives = lives;
	m_points = points;
	m_font.loadFromFile("PAC-FONT.ttf"); 
	t_font.loadFromFile("crackman.ttf");
	setToolBar(); 
	setToolGame();
}

void GameTime::setToolBar()
{
	m_lives_text.setFont(m_font);
	m_lives_text.setCharacterSize(30);
	m_lives_text.setFillColor(Color::Red);
	m_lives_text.setStyle(Text::Bold);
	m_lives_text.setPosition(700, 100);
	m_lives_text.setString("LIVES");
	m_points_text.setFont(m_font);
	m_points_text.setCharacterSize(30);
	m_points_text.setFillColor(Color::Blue);
	m_points_text.setStyle(Text::Bold);
	m_points_text.setPosition(700, 190);
	m_points_text.setString("SCORE");
	m_speed_text.setFont(m_font);
	m_speed_text.setCharacterSize(30);
	m_speed_text.setFillColor(Color::Green);
	m_speed_text.setStyle(Text::Bold);
	m_speed_text.setPosition(700, 280);
	m_speed_text.setString("SPEED");
	m_level_text.setFont(m_font);
	m_level_text.setCharacterSize(30);
	m_level_text.setFillColor(Color::White);
	m_level_text.setStyle(Text::Bold);
	m_level_text.setPosition(60, 10);
	m_level_text.setPosition(700, 10);
	m_level_text.setString("LEVEL");
}

void GameTime::setToolGame()
{
	m_num_lives.setString(to_string(m_lives));
	m_num_lives.setFont(t_font);
	m_num_lives.setStyle(Text::Bold);
	m_num_lives.setCharacterSize(30);
	m_num_lives.setPosition(730, 135);
	m_num_lives.setFillColor(Color::Red);
	m_num_points.setString(to_string(m_points));
	m_num_points.setFont(t_font);
	m_num_points.setStyle(Text::Bold);
	m_num_points.setCharacterSize(40);
	m_num_points.setPosition(730, 225);
	m_num_points.setFillColor(Color::Blue);
	m_num_speed.setString(to_string(m_speed));
	m_num_speed.setFont(t_font);
	m_num_speed.setStyle(Text::Bold);
	m_num_speed.setCharacterSize(40);
	m_num_speed.setPosition(730, 315);
	m_num_speed.setFillColor(Color::Green);
	m_num_level.setString(to_string(m_level));
	m_num_level.setFont(t_font);
	m_num_level.setStyle(Text::Bold);
	m_num_level.setCharacterSize(40);
	m_num_level.setPosition(730, 45);
	m_num_level.setFillColor(Color::White);
}

void GameTime::set_speed(float new_speed)
{
	m_speed = (int)new_speed;
	setToolBar();
	setToolGame();
}

void GameTime::set_lives(int new_lives)
{
	m_lives = new_lives;
	setToolBar();
	setToolGame();
}

void GameTime::set_points(int new_points)
{
	m_points = new_points;
	setToolBar();
	setToolGame();
}

void GameTime::draw(RenderWindow & window)
{
	window.draw(m_level_text);
	window.draw(m_points_text);
	window.draw(m_speed_text);
	window.draw(m_lives_text);
	window.draw(m_num_level);
	window.draw(m_num_speed);
	window.draw(m_num_points);
	window.draw(m_num_lives);
}