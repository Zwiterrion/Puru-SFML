#include "Croix.h"
#include "Position.h"
#include <string>
#include <cstdlib>
#include "Const.h"

using namespace std;

Croix::Croix():Case() // Appel du constructeur de la class Mère
{
    m_obj=" ";
    set_pos(rand()%WIDTH_GAME, rand()%HEIGHT_GAME);
}
