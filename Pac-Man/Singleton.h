#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
class Singleton
{
public:
	static Singleton& show();
	Texture *get_pic(int pic_num);
	~Singleton();
private:
	Singleton();
	Singleton(const Singleton&) = delete;
	Singleton &operator=(const Singleton&) = delete;
	Texture pic_arr[100];
};