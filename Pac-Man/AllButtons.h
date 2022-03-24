#pragma once
#include <SFML\Graphics.hpp>
#include "Singleton.h"
using namespace std;
using namespace sf;

class AllButtons
{
public:
	AllButtons() { m_text = Singleton::show().get_pic(5); };
	virtual void ClickOn(Vector2f pos, RenderWindow& window, bool& exit_on) = 0;
	virtual void draw(RenderWindow& window) = 0;
	virtual Sprite getSprite() = 0;
	virtual void moveOn(Vector2f pos) = 0;
	virtual ~AllButtons() {};
protected:
	Texture* m_text;
	Sprite m_sprite;
	Sprite m_button_on;
	Sprite m_button_before;
};