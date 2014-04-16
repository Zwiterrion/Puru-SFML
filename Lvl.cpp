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
}
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
}




