#include <ctime>
#include <iostream>
#include <cstdlib>
#include "Position.h"
#include "Const.h"

Position::Position(){
    m_x=rand()%(WIDTH_GAME);
    m_y=rand()%(WIDTH_GAME);
}

Position::Position(int x, int y){
    m_x=x;
    m_y=y;
}

void Position::set_x(int x){
    m_x=x;
}

void Position::set_y(int y){
    m_y=y;
}

int Position::get_x() const{
    return m_x;
}

int Position::get_y() const{
    return m_y;
}

void Position::set_pos(int x, int y){
    m_x=x;
    m_y=y;
}
