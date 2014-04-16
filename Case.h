//
//  Case.h
//  THE_PURU
//
//  Created by sayw00t on 24/02/2014.
//  Copyright (c) 2014 sayw00t. All rights reserved.
//

#ifndef __THE_PURU__Case__
#define __THE_PURU__Case__

#include <iostream>
#include <string>
#include "Position.h"

class Case : public Position{ 

protected:
    std::string m_obj;

public:
    Case();
    void add_o(std::string o);
    virtual std::string getObj() const;  // retourne l'objet

};
#endif /* defined(__THE_PURU__Case__) */
