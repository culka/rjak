// Basic renderer class implementation for rjak using SDL
//
// Teemu Mäkinen <culkah@gmail.com> 2014

#include "renderer.h"
#include "rendererror.h"
#include "lbxopen.h"
#include "colors.h"

// Do the standard SDL stuff just in case
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const Uint32 rmask = 0xff000000;
const Uint32 gmask = 0x00ff0000;
const Uint32 bmask = 0x0000ff00;
const Uint32 amask = 0x000000ff;
#else
const Uint32 rmask = 0x000000ff;
const Uint32 gmask = 0x0000ff00;
const Uint32 bmask = 0x00ff0000;
const Uint32 amask = 0xff000000;
#endif

// Move to the next/previous animation frame
void operator++(ANIM_FRAME &af) {
	if (af == ANIM_WALK1) af = ANIM_IDLE;
	else if (af == ANIM_IDLE) af = ANIM_WALK2;
	else if (af == ANIM_WALK2) af = ANIM_ATTACK;
	else af = ANIM_WALK1;
}

void operator--(ANIM_FRAME &af) {
	if (af == ANIM_WALK1) af = ANIM_ATTACK;
	else if (af == ANIM_IDLE) af = ANIM_WALK1;
	else if (af == ANIM_WALK2) af = ANIM_IDLE;
	else af = ANIM_WALK2;
}

// Uses default values
Renderer::Renderer() : mainWindow_(nullptr), renderer_(nullptr),
                       screen_(nullptr), screenSurface_(nullptr),
                       xsize_(ORIGINAL_WIDTH), ysize_(ORIGINAL_HEIGHT),
                       mousexsize_(30), mouseysize_(28),
                       settlerLoaded_(0) {

}

// Takes screen x and y resolution as parameters
Renderer::Renderer(int xsize, int ysize) : mainWindow_(nullptr),
                                           renderer_(nullptr),
                                           screen_(nullptr),
                                           screenSurface_(nullptr), 
                                           xsize_(xsize), ysize_(ysize),
                                           settlerLoaded_(0) {

}

// Renderer::start()
// Initializes the renderer, returns true on error, otherwise false
bool Renderer::start() {
	if ((mainWindow_ = SDL_CreateWindow("Rjak", SDL_WINDOWPOS_UNDEFINED,
	      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0)) == 0) return true;
    if ((renderer_ = SDL_CreateRenderer(mainWindow_, 0, SDL_RENDERER_ACCELERATED)) == 0) return true;
	screenSurface_ = SDL_CreateRGBSurface(0, ORIGINAL_WIDTH, ORIGINAL_HEIGHT, 32, rmask, gmask, bmask, amask);
    screen_ = SDL_CreateTexture(renderer_, screenSurface_->format->format , SDL_TEXTUREACCESS_STREAMING, ORIGINAL_WIDTH, ORIGINAL_HEIGHT);
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    SDL_RenderClear(renderer_);
	SDL_RenderPresent(renderer_);
    mousexsize_ = (30*(SCREEN_WIDTH/ORIGINAL_WIDTH));
    mouseysize_ = (28*(SCREEN_HEIGHT/ORIGINAL_HEIGHT));

    return false;
}

Renderer::~Renderer() {
	// Delete everything that needs to be deleted
	while (!images_.empty()) {
		while(!images_.back()->images.empty()) {
			SDL_FreeSurface(images_.back()->images.back());
			images_.back()->images.pop_back();
		}
		delete images_.back();
		images_.pop_back();
	}

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(mainWindow_);
}

// Grabs a color value from the palette array and makes it 32 bit on the specified position
// No error checking, as it would slow things down and this is slow enough already
void Renderer::draw8bitPixel(SDL_Surface* surface, uint8_t color, int x, int y, std::vector<SDL_Color>* palette) {
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (y * surface->pitch) + (x * sizeof(Uint32)); // get position
    // Use palette if it exists, otherwise use the default one
    if (palette != nullptr) {
		if (color == 232) *((Uint32*)pixel) = SDL_MapRGBA(surface->format, (*palette)[color].r, (*palette)[color].g, (*palette)[color].b, 64);
		else *((Uint32*)pixel) = SDL_MapRGBA(surface->format, (*palette)[color].r, (*palette)[color].g, (*palette)[color].b, 255);
    }
    else {
    	if (color == 232) *((Uint32*)pixel) = SDL_MapRGBA(surface->format, colorpalette[color].r, colorpalette[color].g, colorpalette[color].b, 64);
    	else *((Uint32*)pixel) = SDL_MapRGBA(surface->format, colorpalette[color].r, colorpalette[color].g, colorpalette[color].b, 255);
    }
}

/* Renderer::loadImage
 * 
 * LBXAnimation* image - image to be loaded into memory
 * 
 */
void Renderer::loadImage(LBXAnimation* image) {
	// Something went wrong, throw it back
	if (image == nullptr) {
		throw RenderError(NO_SOURCE);
	}
	
	// There's 14*8 identical settlers, but we really only need 8
	if (image->name == "SETTLERS") {
		if (settlerLoaded_ > 8) {
			return;
		}
		
		settlerLoaded_++;
	}

	std::vector<SDL_Color>* palette = nullptr;

	// If an associated palette exists, translate it into 32 bit colors
	if (image->palette.get() != nullptr) {
		palette = new std::vector<SDL_Color>;
		palette->resize(256);
		uint16_t i = 0;
		// Use default values until first defined color is reached
		for (; i < image->palette.get()->firstColor; ++i) {
			(*palette)[i] = colorpalette[i];
		}
		// Load the amount of given colors
		for (uint16_t c = 0; c < image->palette.get()->colorCount; ++c) {
			// For some reason, the colors use a whole byte per R, G and B,
			// but it needs to be multiplied by 4
			(*palette)[i] = {uint8_t(image->palette.get()->data[c*3]*4), 
			                 uint8_t(image->palette.get()->data[c*3+1]*4),
			                 uint8_t(image->palette.get()->data[c*3+2]*4)};
			++i;
		}
		// Use default colors for the rest
		for (; i < 256; ++i) {
			(*palette)[i] = colorpalette[i];
		}
	}

    int imagenum = 0;
	std::vector<SDL_Surface*> readySurfaces;

	// This translates the RLE encoded image data into one we can use
	// Ignore this unless you _really_ care about it
	for (uint16_t i = 0; i < image->numFrames; ++i) {

		SDL_Surface* img = SDL_CreateRGBSurface(0, image->width, image->height, 32, rmask, gmask, bmask, amask);
		uint32_t pos = image->frame[i] - image->frame[0];

		// If the first byte is 0, draw this image on top of the previous one
		if (image->data[pos] == 0 && imagenum > 0) {
			SDL_BlitSurface(readySurfaces.back(), 0, img, 0);
		}
		++pos;

		// Draw the image from top to bottom, column by column
		for (int x = 0; x < image->width; ++x) {
			if (pos >= (uint16_t)(image->frame[i + 1] - image->frame[0])) break; // Additional exit condition

			uint8_t type = image->data[pos]; // Do stuff depending on the line definition, needed later
			if (type == 0xFF) {
				++pos; // 0xFF = empty column
				continue;
			}
			else if (type == 0x00 || type == 0x80) { // 0x00 means single pixels, 0x80 signifies RLE encoded ones
				uint32_t y = 0;
				uint32_t nextCol = pos + image->data[pos + 1]; // first byte tells the column data length
				pos += 2;
				while (pos < nextCol) { // Do this until column data ends
					uint8_t runLength = image->data[pos]; // This byte tells the RLE length
					y += image->data[pos + 1]; 	// Next one is y offset, for empty space
					pos += 2;
					for (uint8_t i = 0; i < runLength; ++i) { // Run the whole length
						uint8_t value = image->data[pos + i]; // Value is a magic number, containing amount and color

						if (type == 0x80 && value > 0xDF) { // RLE
							value -= 0xDF; // Reduce by 0xDF to get amount, keep track of this
							while (value > 0) {
								draw8bitPixel(img, image->data[pos + i + 1], x, y, palette);
								++y;
								--value; // Repeat this color down the row until value runs out
							}
							++i;
						}
						else { // No special encoding, just draw it
							draw8bitPixel(img, value, x, y, palette);
							++y;
						}
					}
					pos += runLength; // Move to next run/row
				}
			}
			else {
				//std::cout << "Something broke at " << pos << std::endl;
				break; // something went wrong
			}
		}
		// Set SDL's own RLE on to make it's usage faster
		SDL_SetSurfaceRLE(img, 1);
		readySurfaces.push_back(img);
	}

	// Add the ready images into memory
	addImage(image->name, readySurfaces);
}

/* Renderer::drawFrame()
 * 
 * Draws the screen as it has been loaded
 * 
 * Clears the screen surface afterwards, so it's ready for use
 */
void Renderer::drawFrame() {
    SDL_RenderClear(renderer_);
	SDL_UpdateTexture(screen_, NULL, screenSurface_->pixels, screenSurface_->pitch);
	SDL_RenderCopy(renderer_, screen_, 0, 0);
	SDL_RenderPresent(renderer_);
    SDL_FillRect(screenSurface_, 0, SDL_MapRGBA(screenSurface_->format, 0, 0, 0, 255));	
}

/* Renderer::addImage
 * 
 * std::string& name 
 *    Name of the image, used to identify each set of images
 *
 * std::vector<SDL_Surface*> &surfaceset
 *    Vector of some images associated with the name
 */
void Renderer::addImage(std::string& name, std::vector<SDL_Surface*> &surfaceset) {
	
	// Find if the name exists already
	for (unsigned int i = 0; i < images_.size(); ++i) {
		if (images_[i]->name == name) {
			while (!surfaceset.empty()) {
				images_[i]->images.push_back(surfaceset.front());
				surfaceset.erase(surfaceset.begin());
			}
			
			return;
		}
	}
	
	// Add a new Image at the end
	images_.emplace_back(new Image(name));
	while (!surfaceset.empty()) {
		// This is bad, but there's only something like 4 images per set
		images_.back()->images.push_back(surfaceset.front());
		surfaceset.erase(surfaceset.begin());
	}
}

/* Image* Renderer::getImage
 *
 *   Finds an Image associated with the given name
 * 
 *  std::string &name
 *    The name we seek the Image by
 * 
 * returns the Image, or nullptr if none is found
 */
Image* Renderer::getImage(std::string &name) {
	for (unsigned int i = 0; i < images_.size(); ++i) {
		if (images_[i]->name == name) return images_[i];
	}
	
	return nullptr;
}

/* Renderer::drawImage
 * 
 *   Draws a given frame from the Image on
 *    (xpos, ypos) as it's top left corner
 * 
 *  Image* source
 *    Image to be used
 * 
 *  int xpos, int ypos
 *    Coordinates which to draw it
 * 
 *  int frame
 *    frame, that is known to exist
 * 
 *  Throws back a renderError if source is not found, or
 */
void Renderer::drawImage(Image* source, int xpos, int ypos, int frame) {
	// Something went wrong, throw it back
	if (source == nullptr) {
		throw RenderError(NO_SOURCE);
	}
    if (source->images.size() < (unsigned int)frame) {
        throw RenderError(OVER_INDEX, frame);
    }
	
	SDL_Rect r;
	r.x = xpos;
	r.y = ypos;
	
	SDL_BlitSurface(source->images[frame], 0, screenSurface_, &r);
	
}

/* Renderer::drawFigure
 * 
 *   Draws a given animation frame, heading of the given Image on
 *    (xpos, ypos) as it's top left corner
 * 
 *  Image* source
 *    Image to be used
 * 
 *  int xpos, int ypos
 *    Coordinates which to draw it
 * 
 *  UNIT_HEADING heading
 *    Heading used to choose the right frame
 * 
 *  ANIM_FRAME frame
 *    Frame of the heading to be used
 * 
 *  Throws back a renderError if source is not found, or
 */
void Renderer::drawFigure(Image* source, int xpos, int ypos,
                          UNIT_HEADING heading, ANIM_FRAME frame) {
	// Something went wrong, throw it back
	if (source == nullptr) {
		throw RenderError(NO_SOURCE);
	}
    if (source->images.size() < (unsigned int)heading + (unsigned int)frame) {
        throw RenderError(OVER_INDEX, (int)heading + (int)frame);
    }
	
	SDL_Rect r;
	r.x = xpos;
	r.y = ypos;
	
	SDL_BlitSurface(source->images[(int)heading + (int)frame], 0, screenSurface_, &r);
}

/* Renderer::updateMouse
 *
 * int x, int y : mouse cursor position
 * 
 * Updates only the mouse over the old rendered screen
 */
void Renderer::updateMouse(int xpos, int ypos) {
    SDL_Rect r = {xpos, ypos, mousexsize_, mouseysize_};
    SDL_RenderClear(renderer_);
	SDL_RenderCopy(renderer_, screen_, 0, 0);
    SDL_RenderCopy(renderer_, mouse_, 0, &r);
	SDL_RenderPresent(renderer_);    
}

/* Renderer::setMouse
 * 
 * Image* source
 *    Source image which to use
 * 
 * int frame
 *    frame of the image to use
 */
void Renderer::setMouse(Image* source, int frame) {
	if (source == nullptr) {
		throw RenderError(NO_SOURCE);
	}
    if (source->images.size() < (unsigned int)frame) {
        throw RenderError(OVER_INDEX, frame);
    }
    mouse_ = SDL_CreateTextureFromSurface(renderer_, source->images[frame]);    
}
