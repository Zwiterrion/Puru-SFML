//
//  langage.cpp
//  Puru
//
//  Created by Etienne on 11/05/2014.
//  Copyright (c) 2014 Etienne. All rights reserved.
//

#include "Langage.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

Langage::Langage():m_nom("francais"){
    chargementLangue();
}
Langage::Langage(string nom): m_nom(nom)
{
    chargementLangue();
}
Langage::~Langage()
{

}
void Langage::chargementFrancais(){

    if(m_langages.size() != 0)
        m_langages.clear();

    m_langages[0] = "Jouer";
    m_langages[1] = "Option";
    m_langages[2] = "Quitter";
    m_langages[3] = "Score Bonus: ";
    m_langages[4] = "\nBonus Temps: ";
    m_langages[5] = "\nBonus Vie: ";
    m_langages[6] = "\nNiveau: ";
    m_langages[7] = "Score deplacement: ";
    m_langages[8] = "\nScore cible: ";
    m_langages[9] = "\nTemps restant: ";
    m_langages[10] = "\nVie du joueur: ";
    m_langages[11] = "Puru Puru Digger";
    m_langages[12] = "Vous avez perdu ou décider d'abandonner !\nVoulez-vous rejouer ? ";
    m_langages[13] = "\nVous venez de perdre une vie !";
    m_langages[14] = "Voulez-vous continuer ?";
    m_langages[15] = "Vous avez change de niveau ! ";
    m_langages[16] = " \nPlus de temps.Perte de Vie!";
    m_langages[17] = "\t\t\nLe score total: ";
    m_langages[18] = "Vous n'avez plus de vies. Entrez Votre nom :";
    m_langages[19] = "Langues";
    m_langages[20] = "Meilleurs scores";
}
void Langage::chargementLangue() {

    if(m_nom == "francais") {
        chargementFrancais();
    }
    if(m_nom == "anglais")
        chargementAnglais();
}
void Langage::chargementAnglais(){

    if(m_langages.size() != 0)
        m_langages.clear();

    m_langages[0] = "Play";
    m_langages[1] = "Option";
    m_langages[2] = "Exit";
    m_langages[3] = "Score Bonus: ";
    m_langages[4] = "\nBonus Time: ";
    m_langages[5] = "\nBonus Life: ";
    m_langages[6] = "\nLevel: ";
    m_langages[7] = "Movement score: ";
    m_langages[8] = "\nTarget score: ";
    m_langages[9] = "\nRemaining time: ";
    m_langages[10] = "\nPlayer's Life: ";
    m_langages[11] = "Puru Puru Digger";
    m_langages[12] = "You lose or decide to leave! Do you want to play again?";
    m_langages[13] = "\nYou lost a life ! ";
    m_langages[14] = "Do you want to continue ?";
    m_langages[15] = "Do you want to change level ? ";
    m_langages[16] = "\nMore time.Loss of Life !";
    m_langages[17] = "\t\t\nTotal score:  ";
    m_langages[18] = "You do not have lives. Enter your name:";
    m_langages[19] = "Languages";
    m_langages[20] = "Best Scores";
}
void Langage::setNom(std::string nom){
    m_nom = nom;
    chargementLangue();
}
string Langage::getNom() const {
    return m_nom;
}
map<int,std::string> Langage::getlangues() const {
    return m_langages;
}


