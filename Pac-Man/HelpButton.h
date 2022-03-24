#pragma once
#include "AllButtons.h"
using namespace std;
using namespace sf;
class HelpButton :public AllButtons
{
public:
	HelpButton();
	virtual void ClickOn(Vector2f pos, RenderWindow &window, bool & exit_on);
	virtual Sprite getSprite() { return m_sprite; };
	virtual void moveOn(Vector2f pos);
	virtual void draw(RenderWindow & window);
	~HelpButton();
private:
	bool m_button_help;
};