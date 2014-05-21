#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Case.h"
#include "Const.h"

using namespace std;

Case::Case(){
    m_obj = ELEM[rand()%(NB_ELEM)];
}
Case::Case(string ob): m_obj(ob){

}
void Case::add_o(string o){
    m_obj=o;
}
// retourne l'objet (utiliser pour la matrice)
string Case::getObj() const
{
    return m_obj;
}
Case::~Case(){}

int Case::getMov() const{
    return atoi(this->getObj().c_str());
}