// rendererror.h
//
// Teemu Mäkinen <culkah@gmail.com> 2014


#ifndef RENDERERROR_H_
#define RENDERERROR_H_

enum ERRORTYPE {
    NO_SOURCE,
    OVER_INDEX
};

class RenderError {
 public:
    RenderError(ERRORTYPE error, int value = 0);
    ~RenderError();
    
    ERRORTYPE getError() const;
    int getValue() const;
    
 private:
    const ERRORTYPE error_;
    const int value_;
};

#endif
