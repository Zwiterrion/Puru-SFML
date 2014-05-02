//
//  GameModel.h
//  THE_PURU
//
//  Created by sayw00t on 24/02/2014.
//  Copyright (c) 2014 sayw00t. All rights reserved.
//

#ifndef __THE_PURU__GameModel__
#define __THE_PURU__GameModel__

#include <iostream>
#include <string>
#include <map>
#include "Player.h"
#include "Case.h"
#include "BonusCase.h"
#include "Const.h"
#include "Bomb.h"
#include "Lvl.h"
#include "Croix.h"
#include "Score.h"

class GameModel{
private:
    Case*** matrice; // Matrice de pointeurs
    Player *m_p;
    Lvl *m_n;
    Score *m_s;
    Bomb **m_b;
    std::string m_answer_move;
    bool m_continuer;
    int nb_cases;
    int i;
    bool fin;
    
    int goToView;

public:
    GameModel();
    ~GameModel();
    void set_answer_move(std::string a);
    std::string get_answer_move();

    const Player& getPlayer() const;
    const Score& getScore() const;
    const Lvl& getLvl() const;

    void setMatrice(Case*** matriceBis);
    void direction(std::string answer);
    int deplacement();
    void move(int x, int y);

    bool endGame();
    bool getEndGame();
    void setEndGame(bool choix);
    void initLevel();
    void perteVie();
    void changeLevel();
    void objectifAtteint();

    void randomBonus();

    Case*** getMatrice() const;
    void genereMatrice();
    
    void rejouerPartie();
    void tabScore();


    void setGoToView(int t);
    int getGoToView();
};


#endif /* defined(__THE_PURU__GameModel__) */

