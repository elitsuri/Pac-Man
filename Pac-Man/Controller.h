#pragma once
#include "Deamon.h"
#include "Pacman.h"
#include "Cookie.h"
#include "Level.h"
#include "Wall.h"
#include "Objects.h"
#include "Singleton.h"
#include <Vector>
#include <time.h>
#include "windows.h"
#include "GameTime.h"
using namespace std;
using namespace sf;

class Controller
{
public:
	Controller(); 
	void run(); 
private:
	vector <struct keep_info> deamons;
	vector <Deamon> m_deamons;
	unique_ptr <Pacman> pacman; 
	Music m_background, m_game_over, m_eating, m_lost;
	Music m_level_end, m_special_cookie, m_bad_cookie, m_good_luck;
	int m_deamons_sum, m_lives, m_cookies_sum, m_points = 0;;
	float m_cookie_clock, m_special_cookie_counter;
	bool m_sound_switch;
	Vector2f special_cookie_loc;
	Sprite background;
	void deamons_vec_build(Level & level);
	void deamons_draw(RenderWindow &win, float clock_sample);
	float distance(float clock_sample);
	void draw(RenderWindow &win, Level &level, float clock_sample, GameTime &menu);
	Vector2f pacman_get_center(int width, int length);
	Vector2f deamon_get_center(Deamon deamon, int width, int length);
	void move(int width, int length, directions_t side, float deamons_t_counter, Level &level, float distance,
			  bool &good, bool &bad, GameTime &menu, RenderWindow &window);
	void create_deamons();
	void check_deamon_bounds(Deamon &deamon, int width, int length);
	void check_pacman_bounds(int width, int length);
	void pacman_colide_check(Vector2f prev, Level &level, int width, int length, bool &good, bool &bad, GameTime &menu,RenderWindow &window);
	void deamons_colide_check(Deamon &deamon,Vector2f prev, Level &level, int width, int length);
	void recreate_deamons();
	void start_over(Level &level);
	void set_speed_by_level(float cookie_sum);
	void cookie_status(bool &good, bool &bad, bool &health, float clock_sample, Level &level, GameTime &menu);
	void game_over(RenderWindow & window);
	void set_next_level(RenderWindow &window);
	void sound_switch();
	void special_cookie(bool &good, bool &bad, bool &health, float clock_sample, Level &level);
};