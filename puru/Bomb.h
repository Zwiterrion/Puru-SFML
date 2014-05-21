//
//  Bomb.h
//  THE_PURU
//
//  Created by sayw00t on 24/02/2014.
//  Copyright (c) 2014 sayw00t. All rights reserved.
//

#ifndef __THE_PURU__Bomb__
#define __THE_PURU__Bomb__

#include <iostream>
#include <string>

#include "Position.h"
#include "Case.h"

class Bomb : public Case{

public:
    Bomb();
    virtual ~Bomb();
    
    
    // BAC À SABLE
public:
    virtual int getMov();
};

#endif /* defined(__THE_PURU__Bomb__) */
