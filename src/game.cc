// The real main loop of the game and everything important is here
// Implementation
// Teemu Mäkinen <teemu.m.makinen@tut.fi> 2013

#include <chrono>
#include <thread>
#include <iostream>

#include "game.h"
#include "renderer.h"
#include "input.h"
#include "lbxopen.h"
#include "resources.h"
#include "rendererror.h"
#include "baseunit.h"
#include "xmlreader.h"
#include "helper.h"

Game::Game() : renderer(nullptr), input(nullptr){

}

Game::~Game() {
	if (renderer != nullptr) {
		delete renderer;
		renderer = nullptr;
	}
	if (input != nullptr) {
		delete input;
		input = nullptr;
	}

	SDL_Quit();
}

bool Game::run() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
	renderer = new Renderer(320,240);
	input = new Input();
    
	LBXopen nooo;
	
	for (unsigned int i = 0; i < resource_figures_size; ++i) {
		std::vector<LBXAnimation*> tempAnimation =
         nooo.openAnimationFile(resource_dir + resource_figures[i]);
		for (unsigned int j = 0; j < tempAnimation.size(); ++j) {
			renderer->loadImage(tempAnimation[j]);
		}
		while (!tempAnimation.empty()) {
			if (tempAnimation.back() != nullptr) {
				delete tempAnimation.back();
				tempAnimation.back() = nullptr;
			}
			tempAnimation.pop_back();
		}
	}

	renderer->start();
	std::this_thread::sleep_for( std::chrono::milliseconds(200) );

	bool running = true;
	SDL_Event event;
	
    XMLReader xml;
    
    xml.open("xml/darkelf.xml");

    xml.readElement("unit");
    xml.readElement("id");
    
	std::string loll = xml.getElementValue();

    xml.close();
    
    Image* im3 = renderer->getImage(loll);
    renderer->setMouse(im3, 2);
	loll = "MOMBACK";
	Image* im = renderer->getImage(loll);
	loll = "CASTLE";
	Image* im2 = renderer->getImage(loll);
    loll = "HALBOW";
    if (im == nullptr || im2 == nullptr) return 0;
	
	int f = 0;
    
    Uint32 FPS_DELAY = 500;
    Uint32 oldtime = SDL_GetTicks() - FPS_DELAY;
    Sint32 mousex = 0;
    Sint32 mousey = 0;
	while(running) {
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) running = false;
            
            if (event.type == SDL_MOUSEMOTION) {
                mousex = event.motion.x;
                mousey = event.motion.y;
            }
		}
        if (oldtime + FPS_DELAY < SDL_GetTicks()) {
            try {
                renderer->drawImage(im, 0, 0, 0);
                renderer->drawImage(im, 0, 0, f);
                renderer->drawImage(im2, 0, 41, 0);
            }
            catch (RenderError &e) {
                std::cout << "Renderer eror: ";
                if (e.getError() == NO_SOURCE) {
                     std::cout << "no source image found" << std::endl;
                }
                else if (e.getError() == OVER_INDEX) {
                    std::cout << "over index " << e.getValue()
                    << " in image " << std::endl;
                }
            }
            ++f;
            if (f > 7) f = 0;
            renderer->updateMouse(mousex, mousey);
            renderer->drawFrame();
            oldtime = SDL_GetTicks();
        }
        else {
            renderer->updateMouse(mousex, mousey);
        }
	}

	return 0;
}

void Game::loadUnits() {
    XMLReader xml;
    for (unsigned int i = 0; i < resource_unit_stats_size; ++i) {
        xml.open(resource_xml_dir + resource_unit_stats[i]);
        
        for (unsigned int n = 0; ;++n)
        {
            if (xml.readElement("unit", n)) break;
                                    
            xml.readElement("name");
            std::string name = xml.getElementValue();
            xml.closeElement();
            
            xml.readElement("id");
            std::string id = xml.getElementValue();
            xml.closeElement();
            
            xml.readElement("desc");
            std::string description = xml.getElementValue();
            xml.closeElement();
            
            xml.readElement("cost");
            int cost = stringToInt(std::string(xml.getElementValue()));
            xml.closeElement();
            
            xml.readElement("upkeep");
            int goldupkeep = stringToInt(std::string(xml.getAttributeValue("gold")));
            int foodupkeep = stringToInt(std::string(xml.getAttributeValue("food")));
            int manaupkeep = stringToInt(std::string(xml.getAttributeValue("mana")));
            xml.closeElement();
            
            xml.readElement("units");
            int units = stringToInt(std::string(xml.getElementValue()));
            xml.closeElement();
            
            xml.readElement("health");
            int health = stringToInt(std::string(xml.getElementValue()));
            xml.closeElement();
            
            xml.readElement("attack");
            int attack = stringToInt(std::string(xml.getElementValue()));
            xml.closeElement();
            
            int ranged = 0;
            int ammo = 0;
            RANGEDTYPE rangedtype = RANGED_NONE;
            if (xml.readElement("ranged")) {
                ranged = stringToInt(std::string(xml.getElementValue()));
                ammo = stringToInt(std::string(xml.getAttributeValue("ammo")));
                std::string rangedTypeString = xml.getAttributeValue("type");
                xml.closeElement();
                
                if (rangedTypeString == "MAGIC") {
                    rangedtype = RANGED_MAGIC;
                }
                else if (rangedTypeString == "MISSILE") {
                    rangedtype = RANGED_MISSILE;
                }
                else if (rangedTypeString == "STONE") {
                    rangedtype = RANGED_STONE;
                }
            }
            
            xml.readElement("defense");
            int defense = stringToInt(std::string(xml.getElementValue()));
            xml.closeElement();
            
            xml.readElement("resistance");
            int resistance = stringToInt(std::string(xml.getElementValue()));
            xml.closeElement();
                        
            xml.readElement("movement");            
            int movement = stringToInt(std::string(xml.getElementValue()));
            MOVEMENTTYPE movementtype = MOVETYPE_WALK;
            std::string movementTypeString = xml.getAttributeValue("type");
            if (movementTypeString == "WALK") {
                movementtype = MOVETYPE_WALK;
            }
            else if (movementTypeString == "SWIM") {
                movementtype = MOVETYPE_SWIM;
            }
            else if (movementTypeString == "FLY") {
                movementtype = MOVETYPE_FLY;
            }
            else if (movementTypeString == "WALKSWIM") {
                movementtype = MOVETYPE_SWIM | MOVETYPE_WALK;
            }
            xml.closeElement();
        }
        
        xml.close();
    }
}

