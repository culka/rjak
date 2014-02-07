// button.h
// Clickable interface button, with freeform graphics representation
// Teemu Mäkinen <teemu.m.makinen@tut.fi> 2013

// TODO: Add dynamic text support, ie: wait for fonts to work

#ifndef BUTTON_H_
#define BUTTON_H_

#include <utility>
#include <vector>

class Image;

// TODO: Add all button types
enum BUTTONID {
    BUTTON_NONE,
    BUTTON_MAINMENU_NEWGAME,
    BUTTON_MAINMENU_LOADGAME,
    BUTTON_MAINMENU_QUIT,
    BUTTON_MENU_FILE
};

class Button {
 public:
    Button(int x, int y, int w, int h, BUTTONID function);
    ~Button();
    
    void addStateImage(Image* image, int frame);
    std::pair<Image*, int>* getImage(unsigned int state) const;
    bool mouseOver(int x, int y) const;
    BUTTONID getType() const;
    
 private:
    std::vector< std::pair<Image*,int>* > frame_;
    const int x_;
    const int y_;
    const int w_;
    const int h_;
    const BUTTONID function_;
};

#endif

