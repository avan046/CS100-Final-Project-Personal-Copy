#pragma once
#ifndef Game_h
#define Game_h
#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include "ECS/Components.h"
#include <iostream>
#include <vector>;
class ColliderComponent;
class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool isRunning();
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static void AddTile(int x, int y);
	static std::vector<ColliderComponent*> colliders;
private:
	bool running;
	SDL_Window* window;

};
#endif 