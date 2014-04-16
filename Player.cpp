#include "Player.h"
#include "Position.h"
#include <string>
#include <cstdlib>
#include <sstream>
#include "Const.h"

using namespace std;

Player::Player(): Case(){
    m_obj="$$$";
    m_vie =3;
    set_pos(rand()%(WIDTH_GAME), rand()%(HEIGHT_GAME));
}
void Player::set_position(int x, int y){
    while(x>WIDTH_GAME || x<0 || y<0 || y>HEIGHT_GAME){
        if (x>WIDTH_GAME || x<0) {
            cout << "x : ";
            cin >> x;
        }
        if (y>HEIGHT_GAME || y<0){
            cout << "y : ";
            cin >> y;
        }
    }
    set_pos(x, y);
}

int Player::getVie() const
{
    return m_vie;
}
void Player::setVie(int nb)
{
     m_vie = nb;
}
void Player::deplacement(int x, int y)
{
    this->set_pos(this->get_x() + x, this->get_y() + y);
}

