// The real main loop of the game and everything important is here
//
// Teemu Mäkinen <teemu.m.makinen@tut.fi> 2013

#ifndef GAME_H_
#define GAME_H_

#include <vector>

class Renderer;
class Input;
class BaseUnit;

class Game
{
public:
	Game();
	~Game();

	bool run();

private:

	Renderer* renderer;
	Input* input;

    std::vector<BaseUnit*> baseunits_;

    void loadUnits();
};

#endif
