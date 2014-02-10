// rjak main file, really just starts the whole program
// Yeah
//
// Teemu Mäkinen <culkah@gmail.com> 2014

#include "game.h"

// Just make sure everything is alright, then run the real game
int main(int argc, char* argv[])
{
	int result = 0;
	Game* game = new Game;
	result = game->run();

	delete game;
	game = nullptr;

	return result;
}
