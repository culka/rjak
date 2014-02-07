// rendererror.cc

#include "rendererror.h"

RenderError::RenderError(ERRORTYPE error, int value) : 
                         error_(error), value_(value)
{
}

RenderError::~RenderError() {
}

ERRORTYPE RenderError::getError() const {
    return error_;
}

int RenderError::getValue() const {
    return value_;
}
