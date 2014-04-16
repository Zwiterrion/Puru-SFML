//
//  Score.h
//  THE_PURU
//
//  Created by Etienne on 27/02/2014.
//  Copyright (c) 2014 sayw00t. All rights reserved.
//

#ifndef THE_PURU_Score_h
#define THE_PURU_Score_h
#include <string>

class Score
{
public:
    Score();
    void setDeplacement(int deplacement);
    void setScoreTotal(int score);
    void setCible(int c);
    int getDeplacement() const;
    int getScoreTotal() const;
    int getCible() const;

private:
    int nb_deplacement;
    int nb_score_total;
    int m_cible;
};

#endif
