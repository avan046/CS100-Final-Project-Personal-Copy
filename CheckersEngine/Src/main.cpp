#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Game.h"
#include "GameLogic/GameLogic.h"

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

Game* game = nullptr;
GameLogic gameLogic;


int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("GameWindow", 800, 640, false);

	while (game->running())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}

		//gameLogic.getBoard()->Display();

  /*      cout << "Num Black: " << gameLogic.getBoard()->getInstances('B').size() << endl;
		cout << "Num Red: " << gameLogic.getBoard()->getInstances('R').size() << endl;
		if(gameLogic.getCurrPlayer() == 'R')
			gameLogic.getPlayer().makeMove(gameLogic.getBoard());
		else
			gameLogic.getBot().makeMove(gameLogic.getBoard());
		gameLogic.changeTurns();
		game->setBoard(gameLogic.getBoard());*/

	}
	game->clean();
	delete game;
	_CrtDumpMemoryLeaks();
	system("PAUSE");
	return 0;
}