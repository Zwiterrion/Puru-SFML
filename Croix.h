#ifndef THE_PURU_Croix_h
#define THE_PURU_Croix_h

#include <iostream>
#include <string>

#include "Case.h"

class Croix : public Case{
public:
    Croix();
    virtual ~Croix();
    
    // BAC À SABLE
    virtual int getMov();
};

#endif
