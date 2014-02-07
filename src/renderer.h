// Basic renderer class for rjak using SDL
// Teemu Mäkinen <teemu.m.makinen@tut.fi> 2013

#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL2/SDL.h>
#include <string>
#include <vector>

struct LBXAnimation;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;

const int ORIGINAL_WIDTH = 320;
const int ORIGINAL_HEIGHT = 200;

// Unit heading value for combat figures
// Int values are used to access the right surface on array
enum UNIT_HEADING {
	NORTH = 0,
	NORTHEAST = 4,
	EAST = 8,
	SOUTHEAST = 12,
	SOUTH = 16,
	SOUTHWEST = 20,
	WEST = 24,
	NORTHWEST = 28
};

// One of four combat frames
// Also used to access right surface
// eg. array[(int)UNIT_HEADING + (int)ANIM_FRAME]
enum ANIM_FRAME {
	ANIM_WALK1 = 0,
	ANIM_IDLE = 1,
	ANIM_WALK2 = 2,
	ANIM_ATTACK = 3
};

// Anim frames can be cycled through with ++ and --
void operator++(ANIM_FRAME &af);
void operator--(ANIM_FRAME &af);

// Image holds all graphics associated with a given name
struct Image {
	Image(std::string &name_) : name(name_) {};
	
	std::string name;
	std::vector<SDL_Surface*> images;
};

struct Font {
    
    Font(std::string &name_) : name(name_) {};
    // TODO: A better way to get letter from char. Map?
    std::string name;
    std::vector<SDL_Surface*> letters;
};

/* Renderer
 * Handles anything that has to do with drawing stuff on the screen
 *
 * Singleton 
 */
class Renderer {
public:

	Renderer();
	Renderer(int xsize, int ysize);
	~Renderer();

	// Sets all values, returns true if something went wrong
	// nothrow guarantee
	bool start();

	void loadImage(LBXAnimation* image);
	Image* getImage(std::string &name);
	void drawImage(Image* source, int xpos, int ypos, int frame);
	void drawFigure(Image* source, int xpos, int ypos,
                    UNIT_HEADING heading, ANIM_FRAME frame);
    void updateMouse(int xpos, int ypos);
    void setMouse(Image* source, int frame);
	//void clear();
	void drawFrame();

private:

	void addImage(std::string& name, std::vector<SDL_Surface*> &surface);

	void draw8bitPixel(SDL_Surface* surface, uint8_t color, int x, int y, std::vector<SDL_Color>* palette);
	SDL_Window* mainWindow_;
	SDL_Renderer* renderer_;
    SDL_Texture* mouse_;
	SDL_Texture* screen_;
	SDL_Surface* screenSurface_;
	int xsize_;
	int ysize_;
    int mousexsize_;
    int mouseysize_;
	int settlerLoaded_;
	std::vector<Image*> images_;
};

#endif
