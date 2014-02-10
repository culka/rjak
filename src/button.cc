// button.cc
// Clickable interface button, with freeform graphics representation
// Teemu Mäkinen <culkah@gmail.com> 2014

#include "button.h"
#include "renderer.h"

Button::Button(int x, int y, int w, int h, BUTTONID function) : 
               x_(x), y_(y), w_(w), h_(h), function_(function)
{
}

Button::~Button() {
    while(!frame_.empty()) {
        if (frame_.back() != nullptr) {
            delete frame_.back();
        }
        frame_.pop_back();
    }
}

void Button::addStateImage(Image* image, int frame) {
    frame_.emplace_back(new std::pair<Image*, int>(image, frame));
}

std::pair<Image*, int>* Button::getImage(unsigned int state) const {
    if (state < frame_.size()) {
        return frame_[state];
    }
    return nullptr;
}

bool Button::mouseOver(int x, int y) const {
    if ((x >= x_ && x < x_ + w_) && (y >= y_ && y < y_ + h_)) return true;
    
    return false;
}

BUTTONID Button::getType() const {
    return function_;
}
