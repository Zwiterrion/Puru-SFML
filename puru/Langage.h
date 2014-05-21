//
//  langage.h
//  Puru
//
//  Created by Etienne on 11/05/2014.
//  Copyright (c) 2014 Etienne. All rights reserved.
//

#ifndef __Puru__langage__
#define __Puru__langage__

#include <map>
#include <string>

class Langage {
    
public:
    Langage(std::string nom);
    Langage();
    virtual ~Langage();
    void chargementFrancais();
    void chargementLangue();
    void chargementAnglais();
    
    void setNom(std::string nom);
    std::string getNom() const;
    std::map<int,std::string> getlangues() const;
    
private:
    std::map<int, std::string>m_langages;
    std::string m_nom;
};
#endif /* defined(__Puru__langage__) */
