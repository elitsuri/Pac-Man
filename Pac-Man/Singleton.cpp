#include "Singleton.h"
#include <iostream>

Singleton::Singleton()
{
	pic_arr[0].loadFromFile("pics/pacman.png"); //pacman picture
	pic_arr[1].loadFromFile("pics/deamon.png"); // deamons picture.
	pic_arr[2].loadFromFile("pics/cookie.png"); //cookie picture/
	pic_arr[3].loadFromFile("pics/wall.png");	//wall picture.
	pic_arr[4].loadFromFile("pics/back.jpg"); //background.
	pic_arr[5].loadFromFile("pics/menu_bottons.png"); //the buttons.
	pic_arr[6].loadFromFile("pics/menu_back.png"); //menu background.
	pic_arr[7].loadFromFile("pics/velosity.png"); //velosity cookie.
	pic_arr[8].loadFromFile("pics/poison.png"); //poison cookie.
	pic_arr[9].loadFromFile("pics/lives.png"); //lives cookie.
	pic_arr[10].loadFromFile("pics/gameover.jpg"); //game over picture.
	pic_arr[11].loadFromFile("pics/trophy.png"); //trophy picture.
	pic_arr[12].loadFromFile("pics/lost.png"); //lost picture.
	pic_arr[13].loadFromFile("pics/help.png"); //help picture.
	pic_arr[14].loadFromFile("pics/game_back.png"); //help picture.

	pic_arr[6].setSmooth(true);
	pic_arr[7].setSmooth(true);
	pic_arr[8].setSmooth(true);
}

/////////////////////////////// SHOW /////////////////////////////////
// will make a static object to get a picture.
Singleton &Singleton::show()
{
	static Singleton noun;
	return noun;
}

/////////////////////////////// GET PIC /////////////////////////////////
// return the picture from the array.
sf::Texture * Singleton::get_pic(int pic_num)
{

	return &pic_arr[pic_num];
}


Singleton::~Singleton()
{
}