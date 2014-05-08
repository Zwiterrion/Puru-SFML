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
#include <ctime>

class Lvl {
private:
    int m_lvl;
    int m_nb_bomb;
    int m_nb_bonus;
    int m_bonus_temps;
    int m_bonus_vie;
    int m_score_bonus;
    int m_temps;
    time_t secondes;
    struct tm instant;
    int m_minutes;
    int m_fin;
    int m_compteur;
    int m_difference;
    int m_firstTime;

public:
    Lvl();
    virtual ~Lvl();
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
    int getTemps() const;
    void setTemps(int temps);
    void initTemps();
    void calculDuTemps();
};

#endif /* defined(__THE_PURU__Lvl__) */
