//
//  Editeur.h
//  Puru
//
//  Created by Etienne on 14/05/2014.
//  Copyright (c) 2014 Etienne. All rights reserved.
//

#ifndef __Puru__Editeur__
#define __Puru__Editeur__

#include <string>
#include <vector>

class GameModel;
class Case;
class Player;

class Editeur {
    
public:
    Editeur();
    virtual ~Editeur();
    Case*** getMatriceEditeur() const;
    bool s_verificationPositionMatrice(int x, int y);
    void ajouterBomb(int i, int j, bool isSelecting);
    void ajouterBonus(int i, int j, bool isSelecting);
    void ajouterDigger(int i, int j, bool isSelecting);
    void sauvegardeFichier(std::string nom);
    void chargementListeFichier();
    std::vector<std::string> getFichierRecent() const;
    void setNomFichier(std::string nom);
    void chargerNiveau(std::string nomLevel);
    void changerBooleen(bool val);
    void genereMatriceEditeur();
    
private:
    Case *** _matrice;
    std::vector<std::string>_fichierRecent;
    bool isBomb;
    bool isBonus;
    bool isCase;
    bool isPlayer;
    bool isCroix;
};

#endif /* defined(__Puru__Editeur__) */
