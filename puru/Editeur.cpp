//
//  Editeur.cpp
//  Puru
//
//  Created by Etienne on 14/05/2014.
//  Copyright (c) 2014 Etienne. All rights reserved.
//

#include "Editeur.h"
#include "Case.h"
#include "GameModel.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

Editeur::Editeur() {

    _matrice = new Case** [18];
    for (int i=0; i < 18 ; i++)
        _matrice[i] = new Case*[18];

    for(int i=0; i<18; i++){
        for(int j=0; j<18; j++)
            _matrice[i][j] = new Case();
    }

}
Editeur::~Editeur(){

    /* Allocation dynamique des cases */
    for (int i=0; i < 18; i++){
        for(int j=0; j < 18; j++)
            delete _matrice[i][j];
        delete[] _matrice[i];
    }
    delete[] _matrice;   // Désallocation de la matrice

}
Case*** Editeur::getMatriceEditeur() const{
    return _matrice;
}
bool Editeur::s_verificationPositionMatrice(int x, int y){

    if((x/WIDTH_PIECE) <= 18 && (x/WIDTH_PIECE) >= 1 && (y/WIDTH_PIECE) <= 18 && (y/WIDTH_PIECE) >= 1){
        return true;
    }
    else
        return false;
}
void Editeur::ajouterBomb(int i, int j, bool isSelecting){

    if(s_verificationPositionMatrice(i, j) && isSelecting){
        int x = (i-50)/WIDTH_PIECE;
        int y = (j-30)/WIDTH_PIECE;

        delete _matrice[y][x];
        _matrice[y][x] = new Bomb();
    }

}
void Editeur::ajouterBonus(int i, int j, bool isSelecting){

    if(s_verificationPositionMatrice(i, j) && isSelecting){
        int x = (i-50)/WIDTH_PIECE;
        int y = (j-30)/WIDTH_PIECE;

        delete _matrice[y][x];
        _matrice[y][x] = new BonusCase();
    }

}
void Editeur::sauvegardeFichier(std::string nom) {
    fstream f;
    fstream fichierSauvegardeName;

    ostringstream out;
    out << nom.c_str() << ".txt";
    string e = out.str();
    cout << "e = " << e << endl;

    f.open(e.c_str(), ios::out);

    fichierSauvegardeName.open("fichierSave.txt", ios::out | ios::app);
    if(fichierSauvegardeName.fail()){
        cerr << "Ouverture save impossible" << endl;
    }
    else {
        fichierSauvegardeName << nom << endl;
        cout << "Fichier sauvegardé" << endl;
    }
    if(f.fail()) {
        cerr << "ouverture en lecture impossible dans l'éditeur" << endl;
    }
    for(int i=0; i<18; i++){
        for(int j=0; j<18; j++) {
            if(dynamic_cast<Bomb*>(_matrice[i][j])){
                f << "BOMB" << " " << i << " " << j << endl;
            }
            else if(dynamic_cast<BonusCase*>(_matrice[i][j])){
                f << "BONUS" << " "<< i << " " << j << " " << _matrice[i][j]->getObj() << endl;
            }
            else if(dynamic_cast<Croix*>(_matrice[i][j])){
                f << "CROIX" << " "<< i << " " << j << endl;
            }
            else {
                f << "CASE" << " "<< i << " " << j << " " << _matrice[i][j]->getObj()  << endl;
            }
        }

    }
    fichierSauvegardeName.close();
    f.close();
}
void Editeur::chargementListeFichier(){

    fstream f;
    f.open("fichierSave.txt", ios::in);

    _fichierRecent.resize(0);
    if( f.fail() )
    {
        cerr << "ouverture en lecture impossible dans editer" << endl;
    }
    else
    {
        string phrase;

        getline(f, phrase);

        while(!f.eof()){
            if(phrase != " ")
                _fichierRecent.push_back(phrase);
            getline(f, phrase);
        }

        f.close(); // fermeture du fichier
    }

}
vector<string> Editeur::getFichierRecent() const
{
    return _fichierRecent;
}
void Editeur::chargerNiveau(std::string nomLevel){

    fstream f;

    ostringstream out;
    string e = nomLevel + ".txt";

    cout << "Le nom : " << e << endl;
    f.open(e.c_str(), ios::in);

    if( f.fail() )
    {
        cerr << "ouverture en lecture impossible dans editer-chargement" << endl;
    }
    else
    {
    string phrase;

    int i = 0;
    int j = 0;
    int compteur = 1;

        f >> phrase;
        while(!f.eof()){
            if(compteur == 4){
                compteur = 1;
                if(isBonus){
                   _matrice[i][j] = new BonusCase(phrase);
                }
                if(isCase)
                    _matrice[i][j] = new Case(phrase);
            }
            if(compteur == 3){
                j = atoi(phrase.c_str());
                if(isBonus)
                    compteur++;
                if(isBomb){
                    _matrice[i][j] = new Bomb();
                    compteur = 1;
                }
                if(isCase)
                    compteur++;
                if(isCroix){
                    _matrice[i][j] = new Croix();
                    compteur = 1;
                }
            }
            if(compteur == 2){
                compteur++;
                i = atoi(phrase.c_str());
            }
            if(compteur == 1){
                if(phrase == "BOMB"){
                    compteur++;
                    isBomb = true;
                    isBonus = false;
                    isPlayer = false;
                    isCase = false;
                    isCroix = false;
                }
                if(phrase == "BONUS"){
                    compteur++;
                    isBomb = false;
                    isBonus = true;
                    isPlayer = false;
                    isCase = false;
                    isCroix = false;
                }
                if(phrase == "CASE"){
                    compteur++;
                    isBomb = false;
                    isBonus = false;
                    isPlayer = false;
                    isCase = true;
                    isCroix = false;
                }
                if(phrase == "CROIX"){
                    compteur++;
                    isBomb = false;
                    isBonus = false;
                    isPlayer = false;
                    isCase = false;
                    isCroix = true;
                }
            }
            f >> phrase;
        }
        f.close();
    }
}
void Editeur::genereMatriceEditeur() {

    for (int i=0; i < 18; i++){
        for(int j=0; j < 18; j++)
            delete _matrice[i][j];
    }

    for(int i=0; i<18; i++){
        for(int j=0; j<18; j++)
            _matrice[i][j] = new Case();
    }

}










