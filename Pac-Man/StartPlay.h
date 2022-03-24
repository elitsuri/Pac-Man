#pragma once
#ifdef _DEBUG
#pragma comment(lib, "sfml-main-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#elif defined(NDEBUG)
#pragma comment(lib, "sfml-main.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-audio.lib")
#else		
#error "Unrecognized configuration!"
#endif
#include "AllButtons.h"
#include "StartButton.h"
#include "HelpButton.h"
#include "ExitButton.h"
#include <memory>
using namespace std;
using namespace sf;
class StartPlay
{
public:
	StartPlay();
	void run(bool &exit_on);
	~StartPlay();
private:
	vector<unique_ptr<AllButtons>> m_vector_but;
	bool m_startPlay;
	Sprite m_back;
};