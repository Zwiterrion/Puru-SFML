#include "Lvl.h"
#include <sstream>
#include <iostream>

using namespace std;

Lvl::Lvl(){
    m_lvl = 1;
    m_nb_bomb=10;
    m_nb_bonus = 5;
    m_bonus_temps = 0;
    m_bonus_vie = 0;
    m_score_bonus = 0;
    m_temps = 45;
    initTemps();
}

Lvl::~Lvl(){}
int Lvl::getNb() const
{
    return m_nb_bomb;
}
int Lvl::getBonus() const
{
    return m_nb_bonus;
}
void Lvl::setLevel(int level)
{
    m_lvl = level;
}
void Lvl::setBomb(int nb)
{
    m_nb_bomb = nb;
}
void Lvl::setBonus(int nb)
{
    m_nb_bonus = nb;
}
int Lvl::getLevel() const
{
    return m_lvl;
}

int Lvl::get_b_temps() const
{
    return m_bonus_temps;
}
int Lvl::get_b_vie() const
{
    return m_bonus_vie;
}
int Lvl::get_score_bonus() const
{
    return m_score_bonus;
}
void Lvl::set_bonusVie(int nb)
{
    m_bonus_vie = nb;
}
void Lvl::set_bonusTemps(int nb)
{
    m_bonus_temps = nb;
}
void Lvl::set_score_bonus(int nb)
{
    m_score_bonus = nb;
}
void Lvl::initBonus()
{
    set_bonusVie(0);
    set_bonusTemps(0);
    set_score_bonus(0);
    if(m_lvl%2 == 0) {
        setTemps(47-2);
    }
    else {
        setTemps(45-1);
    }
    if(m_lvl == 10){
        setTemps(35);
    }
}
int Lvl::getTemps() const {
    return m_temps;
}
void Lvl::setTemps(int temps) {
    m_temps = temps;
}
void Lvl::initTemps() {
    time(&secondes);
    instant=*localtime(&secondes);
    m_minutes = instant.tm_min;
    m_compteur =0;
    m_difference = 0;
    m_firstTime = 0;
    m_fin = 0;
}
void Lvl::calculDuTemps()
{
    if(m_firstTime == 0){
        cout << "Temps restant : " << m_temps << endl;
        m_firstTime = 1;
        time(&secondes);
        instant=*localtime(&secondes);
        m_fin = instant.tm_sec;
        m_minutes = instant.tm_min;
        m_compteur = m_minutes * 60+ m_fin;
    }
    else
    {
        time(&secondes);
        instant=*localtime(&secondes);
        m_fin = instant.tm_sec;
        m_minutes = instant.tm_min;
        m_difference = ((m_minutes * 60) + m_fin) - m_compteur;
        m_temps -= m_difference;
        m_compteur = (m_minutes * 60 )+ m_fin;
    
        if(m_temps <= 0)
            m_temps = 0;
    }
    
}




