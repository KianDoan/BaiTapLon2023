#ifndef GAME_H_
#define GAME_H_

#include<iostream>
#include<string>
#include<SDL.h>
#include<SDL_image.h>

#include"LoadTexture.h"
#include"GameObject.h"
#include"Map.h"

using namespace std;

class Game
{

public:
	Game();
	~Game();
	void init(const char* p_title, int p_xPos, int p_yPos, int p_width, int p_height, bool fullScreen);
	void handleEvent();
	void update();
	void render();
	void cleanUp();
	bool gameOver()
	{
		return isOver;
	}
	static SDL_Renderer* renderer;
	void renderBackGround(int p_x, SDL_Texture* p_background_tex);
	int scroll_speed;
private:
	SDL_Window* window;
	bool isOver;

	SDL_Texture* layer_1;
	SDL_Texture* layer_2;
	SDL_Texture* layer_3;
	SDL_Texture* layer_4;
	SDL_Texture* layer_5;
	SDL_Texture* layer_6;
	
	float layer1_x;
	float layer2_x;
	float layer3_x;
	float layer4_x;
	float layer5_x;
	float layer6_x;
	
};

#endif // !GAME_H_
