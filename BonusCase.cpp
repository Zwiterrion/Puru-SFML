#include "BonusCase.h"
#include "Position.h"
#include <string>
#include <cstdlib>
#include "Const.h"

using namespace std;

BonusCase::BonusCase():Case() // Appel du constructeur de la class Mère
{
    string entier = ELEM[rand()%(NB_ELEM)];
    m_obj= "-" + entier + "-";
    set_pos(rand()%WIDTH_GAME, rand()%HEIGHT_GAME);
}
