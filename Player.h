//
//  Player.h
//  THE_PURU
//
//  Created by sayw00t on 24/02/2014.
//  Copyright (c) 2014 sayw00t. All rights reserved.
//

#ifndef __THE_PURU__Player__
#define __THE_PURU__Player__

#include <iostream>

#include "Case.h"
#include "Position.h"

class Player : public Case{
public:
    Player();
    Position get_position();
    void setVie(int nb);
    void deplacement(int x, int y);
    void set_position(int x, int y);
    int getVie() const;
    void move_N();
    void move_NE();
    void move_E();
    void move_SE();
    void move_S();
    void move_SO();
    void move_O();
    void move_NO();

private:
    int m_vie;
};

#endif /* defined(__THE_PURU__Player__) */
