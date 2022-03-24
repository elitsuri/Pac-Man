#pragma once
#include "AllButtons.h"
using namespace std;
using namespace sf;
class StartButton :public AllButtons
{
public:
	StartButton();
	virtual void ClickOn(Vector2f pos, RenderWindow &window, bool & exit_on);
	virtual Sprite getSprite() { return m_sprite; }
	virtual void moveOn(Vector2f pos);
	virtual void draw(RenderWindow & window);
	~StartButton();
};