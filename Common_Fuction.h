#ifndef COMMON_FUCTION_H_
#define COMMON_FUCTION_H_

#include<string>
#include<SDL_ttf.h>

#include"Game.h"

using namespace std;

class Common_Fuction
{
public:
	Common_Fuction();
	~Common_Fuction();
	static SDL_Texture* loadTex(const char* p_path);
private:

};

class Menu
{
public:
	Menu();
	~Menu();

	bool LoadMenu();
	int CheckMouseDown(int p_x,int p_y);

	void close();
private:
	SDL_Texture* main_menu, * play_button, * exit_button;
	SDL_Rect play_button_rect = { 100,50,203,109 }, exit_button_rect = { 100,170,203,109 };

	SDL_Event e;

	int x_mouse;
	int y_mouse;
};

#endif
