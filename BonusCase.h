#ifndef BONUSCASE_H_INCLUDED
#define BONUSCASE_H_INCLUDED

#include <iostream>
#include <string>

#include "Case.h"

class BonusCase : public Case{

public:
    BonusCase();
    virtual ~BonusCase();
    virtual int getMov() const ;
    std::string getEntier() const;

    // BAC À SABLE
private:
    std::string _entier;
    
};

#endif // BONUSCASE_H_INCLUDED
