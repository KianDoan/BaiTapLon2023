#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include<ctime>
#include<cstdlib>

#include"Game.h"
#include"Map.h"

using namespace std;

enum STATUS
{
	MOVE_RIGHT,
	MOVE_LEFT,
	STAND_RIGHT,
	STAND_LEFT,
	RIGHT_FALL,
	LEFT_FALL
};

class GameObject
{
public:
	GameObject(const char* p_path, int p_x, int p_y);
	~GameObject();

	void update(Map& map_data);
	void render();
	void loadClips();
	void renderClip();
	bool handlePlayerInput();
	void CheckToMap(Map& map_data);
	void CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	void scrollMap(Map& map_data);
	SDL_Rect GetRect()
	{
		return destRect;
	}

	void close();

private:
	float x_pos;
	float y_pos;
	int object_scroll;
	int map_scroll;
	int frame;
	int jump;
	int left;
	int right;
	STATUS status;
	float gravity_speed;
	float velocity;
	float jump_speed;
	bool on_ground;
	bool is_dead;
	SDL_Event event;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect, frame_clip[6];
	int lever;
};


//Threat Object


class ThreatObject
{
public:
	ThreatObject(int p_x, int p_y, int p_seed);
	~ThreatObject();

	void Update(Map& map_data);
	void Render();
	bool Accident(Map& map_data);

	SDL_Rect GetRect()
	{
		return dest_rect;
	}

	void close();

private:
	int seed;

	int object_scroll;
	int map_scroll;
	float x_val, y_val;
	SDL_Rect dest_rect;
	SDL_Texture* threat_texture;

};

#endif // !GAME_OBJECT_H_
