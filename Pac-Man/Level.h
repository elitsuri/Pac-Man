#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "StaticObjects.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <cmath>
#include <memory>
using namespace std;
using namespace sf;
struct keep_info
{
	char icon;
	Vector2i location;
};

class Level
{
public:
	Level(int level);
	void draw(RenderWindow& win, float clock_sampleB);
	Vector2i get_pac_location();
	char get_pac_icon();
	struct keep_info get_deamon(int deamon);
	int get_deamons_sum();
	int get_width();
	int get_length();
	StaticObjects* get_object(Vector2f place);
	void cookie_eaten();
	void set_object_null(Vector2f place);
	int get_cookies();
	void set_special_cookie(int x, int y, char icon);
private:
	int m_cookies, m_level, m_width, m_length, m_deamons_sum;
	vector<string> m_file_vector;
	vector<vector<unique_ptr<StaticObjects>>> m_board;
	struct keep_info pacman;
	vector <struct keep_info > deamons;
	void copy_to_file_vector(ifstream& file);
	void define_m_board(vector <string> m_file_vector);
	void make_m_board();
};