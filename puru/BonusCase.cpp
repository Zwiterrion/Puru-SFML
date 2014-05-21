#include "BonusCase.h"
#include "Position.h"
#include <string>
#include <cstdlib>
#include "Const.h"

using namespace std;

BonusCase::BonusCase():Case() // Appel du constructeur de la class Mère
{
    _entier = ELEM[rand()%(NB_ELEM)];
    m_obj= "-" + _entier + "-";
    set_pos(rand()%WIDTH_GAME, rand()%HEIGHT_GAME);
}
BonusCase::BonusCase(std::string ob){
    m_obj= ob;
}
BonusCase::~BonusCase(){}

std::string BonusCase::getEntier()const{
    return _entier;
}



// BAC À SABLE
int BonusCase::getMov() const{
    return atoi(_entier.c_str());
}

