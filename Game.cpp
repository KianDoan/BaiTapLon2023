#include"Game.h"

GameObject* player;

SDL_Renderer* Game::renderer = NULL;

Map* map;

ThreatObject *threat_1, *threat_2, *threat_3;


Game::Game()
	:window(NULL), isOver(false)
{

	layer_1 = NULL;
	layer_2 = NULL;
	layer_3 = NULL;
	layer_4 = NULL;
	layer_5 = NULL;
	layer_6 = NULL;


	layer1_x = 0;
	layer2_x = 0;
	layer3_x = 0;
	layer4_x = 0;
	layer5_x = 0;
	layer6_x = 0;
}

Game::~Game()
{}

void Game::init(const char* p_title, int p_xPos, int p_yPos, int p_width, int p_height, bool fullScreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Failed to init SDL..." << endl;
		isOver = true;
	}
	else
	{
		window = SDL_CreateWindow(p_title, p_xPos, p_yPos, p_width, p_height, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			cout << "Failed to create window..." << endl;
			isOver = true;
		}
		else
		{
			int imgFlag = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlag) & imgFlag))
			{
				cout << "Failed to init IMG..." << endl;
				isOver = true;
			}
			else
			{
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				if (renderer == NULL)
				{
					cout << "Failed to create renderer..." << endl;
					isOver = true;
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
					player = new GameObject("Resources/gfx/right_stand.png", 640, 384);
					player->loadClips();
					threat_1 = new ThreatObject(1280, 1000, 0);
					threat_2 = new ThreatObject(1000, -1240, 1879);
					threat_3 = new ThreatObject(1000, -1480, 900);
					map = new Map();
					layer_1 = Common_Fuction::loadTex("Resources/gfx/layer_1.png");
					layer_2 = Common_Fuction::loadTex("Resources/gfx/layer_2.png");
					layer_3 = Common_Fuction::loadTex("Resources/gfx/layer_3.png");
					layer_4 = Common_Fuction::loadTex("Resources/gfx/layer_4.png");
					layer_5 = Common_Fuction::loadTex("Resources/gfx/layer_5.png");
					layer_6 = Common_Fuction::loadTex("Resources/gfx/layer_6.png");
				}
			}
		}
	}
}

void Game::renderBackGround(int p_x , SDL_Texture* p_background_tex)
{
	SDL_Rect bg_rect = { p_x,0,1280,640 };
	SDL_RenderCopy(renderer, p_background_tex, NULL, &bg_rect);
}

void Game::handleEvent()
{
	if (player->handlePlayerInput())
		isOver = true;
}

void Game::update()
{
	layer2_x -= 0.4;
	if (layer2_x <= -1280)
	{
		layer2_x = 0;
	}
	layer3_x -= 0.8;
	if (layer3_x <= -1280)
	{
		layer3_x = 0;
	}
	layer4_x -= 1.6;
	if (layer4_x <= -1280)
	{
		layer4_x = 0;
	}
	layer5_x -= 2;
	if (layer5_x <= -1280)
	{
		layer5_x = 0;
	}
	layer6_x -= 2.5;
	if (layer6_x <= -1280)
	{
		layer6_x = 0;
	}
	
	map->loadMap();
	player->CheckCollision(player->GetRect(), threat_1->GetRect());
	player->CheckCollision(player->GetRect(), threat_2->GetRect());
	player->CheckCollision(player->GetRect(), threat_3->GetRect());
	player->update(*map);
	threat_1->Update(*map);
	threat_2->Update(*map);
	threat_3->Update(*map);

}

void Game::render()
{
	SDL_RenderClear(renderer);
	renderBackGround(layer1_x, layer_1);
	renderBackGround(layer2_x, layer_2);
	renderBackGround(layer2_x + 1280, layer_2);
	renderBackGround(layer3_x, layer_3);
	renderBackGround(layer3_x + 1280, layer_3);
	renderBackGround(layer4_x, layer_4);
	renderBackGround(layer4_x + 1280, layer_4);
	renderBackGround(layer5_x, layer_5);
	renderBackGround(layer5_x + 1280, layer_5);
	renderBackGround(layer6_x, layer_6);
	renderBackGround(layer6_x + 1280, layer_6);

	map->drawMap();
	player->renderClip();
	threat_1->Render();
	threat_2->Render();
	threat_3->Render();
	SDL_RenderPresent(renderer);
}

void Game::cleanUp()
{
	map->close();
	player->close();
	threat_1->close();
	threat_2->close();
	threat_3->close();
	SDL_DestroyTexture(layer_1);
	SDL_DestroyTexture(layer_1);
	SDL_DestroyTexture(layer_1);
	SDL_DestroyTexture(layer_1);
	SDL_DestroyTexture(layer_1);
	SDL_DestroyTexture(layer_1);
	layer_1 == NULL;
	layer_2 == NULL;
	layer_3 == NULL;
	layer_4 == NULL;
	layer_5 == NULL;
	layer_6 == NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}
