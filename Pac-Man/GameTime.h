#pragma once
#include <SFML\Graphics.hpp>
using namespace std;
using namespace sf;
class GameTime
{
public:
	GameTime(int level,float speed,int lives,int points);
	void setToolBar();
	void setToolGame();
	void set_speed(float new_speed);
	void set_lives(int new_lives);
	void set_points(int new_points);
	void draw(RenderWindow &window);
	~GameTime() {};
private:
	Font m_font, t_font;
	Text m_level_text, m_points_text, m_speed_text, m_lives_text;
	Text m_num_level, m_num_points, m_num_speed, m_num_lives;
	int m_level = 1;
	int m_lives = 3;
	int m_points= 0;
	int m_speed = 1;
};