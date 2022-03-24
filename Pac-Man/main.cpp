#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "StartPlay.h"

int main()
{
	StartPlay start_play; // the menu object
	bool exit_on = true; //check if exit pressed on menu.

	while (exit_on) // while not
		start_play.run(exit_on); //menu is running.
	
	return (EXIT_SUCCESS);
}

