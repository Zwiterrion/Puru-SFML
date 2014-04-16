//
//  Lvl.h
//  THE_PURU
//
//  Created by sayw00t on 24/02/2014.
//  Copyright (c) 2014 sayw00t. All rights reserved.
//

#ifndef __THE_PURU__Lvl__
#define __THE_PURU__Lvl__

#include <iostream>

class Lvl {
private:
    int m_lvl;
    int m_nb_bomb;
    int m_nb_bonus;
    int m_bonus_temps;
    int m_bonus_vie;
    int m_score_bonus;
public:
    Lvl();
    int getNb() const;
    int get_score_bonus() const;
    int get_b_temps() const;
    int get_b_vie() const;
    int getBonus() const;
    int getLevel() const;
    void setBomb(int nb);
    void setBonus(int nb);
    void setLevel(int level);
    void initBonus();
    void set_bonusVie(int nb);
    void set_bonusTemps(int nb);
    void set_score_bonus(int nb);

};

#endif /* defined(__THE_PURU__Lvl__) */
