//
//  GameView.h
//  THE_PURU
//
//  Created by Zwitterion on 24/02/2014.
//  Copyright (c) 2014 sayw00t. All rights reserved.
//

#ifndef __THE_PURU__GameView__
#define __THE_PURU__GameView__

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class GameModel;
class Case;
class Button;
class Langage;
class Editeur;

class GameView{

public:
    GameView(int h, int w, int bpp);
    virtual ~GameView();
    void setModel(GameModel *model);
    void affichageScore();
    bool answer_move(std::string answer);

private:
    GameModel *m_model;
    std::vector<sf::Sprite*> images;
    std::string s_nom;
    std::string s_nom_player;
    bool isEnable;
    std::map<int, std::string>m_e;
    bool afficherScore;
    Langage *m_langue;
    std::map<int,std::string>m_l;

public: // SFML
    void draw(Case ***matrice);
    bool treatEvents();
    void s_Presentation();
    void s_afficheBonus();
    void s_afficheScore();
    void s_viePlayer();
    void s_rejouer();
    void s_perteVie();
    void s_changeLvl();
    void s_plusDeVie();
    void s_option();
    void s_perteParTemps();
    void s_sauvegarde_score();
    void s_chargementScore();
    void s_affichageLangue();
    void s_quitte_inGame();
    void s_boutton_son();

    void s_boutonEditeur();
    void s_affiche_choix();
    void s_verifiationSelectionBomb(const sf::Sprite *s, int x, int y);
    void s_verifiationSelectionBonus(const sf::Sprite *s, int x, int y);
    void s_bouton_save();
    void s_buttonInEdit();
    void s_afficheFichierRecent();
    void s_inscrireNomFichier();
    void loadText(sf::String &s, const int x, const int y, const float size, const std::string text, const sf::Font &f, const int r, const int g, const int b, float a);
    void s_menuDemarrage();

private: // SFML
    std::string _namePictureBackground;     //background.png
    std::string _namePictureDigger;         //digger_face.png
    std::string _namePictureBomb;           //tuile_bombe.png
    std::string _namePictureBonus;          //tuile_bonus.png
    std::string _namePictureCase;           //tuile.png
    std::string _namePictureExitButton;     //exitButton.png
    std::string _namePicturePlayButton;     //startButton.png
    std::string _namePictureCaseVide;       //vide.png
    std::string _namePictureOptionButton;   //optionButton.png
    std::string _namePictureMenu;           //menu.png
    std::string _namePictureBestscore;      //bestScore.png
    std::string _namePictureFrancais;       //francais.png
    std::string _namePictureAnglais;        //anglais.png
    std::string _namePictureJouer;          //jouer.png
    std::string _namePictureQuitter;        //quitter.png
    std::string _namePictureSound;          //son.png
    std::string _namePictureNotSound;       //notSon.png
    std::string _namePictureEditeur;         //Editeur.png
    std::string _namePictureNouveau;
    std::string _namePictureEnregistrer;
    std::string _namePictureCharger;
    std::string _namedigger1;
    std::string _namedigger2;
    std::string _namedigger3_1;
    std::string _namedigger3_2;
    std::string _namedigger3_3;
    std::string _namedigger4;
    std::string _namedigger5;
    std::string _namedigger6;
    std::string _namedigger7;
    std::string _namedigger8;
    std::string _namedigger9;
    std::string _namedigger10;
    std::string _namedigger11;
    std::string _namedigger12;
    std::string _namedigger13;
    std::string _namedigger14;
    std::string _namedigger15;
    std::string _namedigger16;




    sf::RenderWindow *m_window;

    sf::Image _nouveau_image;
    sf::Image _charger_image;
    sf::Image _enregistrer_image;
    sf::Image _background_image;
    sf::Image _digger_image;
    sf::Image _bombe_image;
    sf::Image _tuile_image;
    sf::Image _bonus_image;
    sf::Image _exit_image;
    sf::Image _start_image;
    sf::Image _vide_image;
    sf::Image _option_image;
    sf::Image _menu_image;
    sf::Image _bestScore_image;
    sf::Image _francais_image;
    sf::Image _anglais_image;
    sf::Image _jouer_image;
    sf::Image _quitter_image;
    sf::Image _son_image;
    sf::Image _notSon_image;
    sf::Image _editer_image;
    
    sf::Image _digger1;
    sf::Image _digger2;
    sf::Image _digger3_1;
    sf::Image _digger3_2;
    sf::Image _digger3_3;
    sf::Image _digger4;
    sf::Image _digger5;
    sf::Image _digger6;
    sf::Image _digger7;
    sf::Image _digger8;
    sf::Image _digger9;
    sf::Image _digger10;
    sf::Image _digger11;
    sf::Image _digger12;
    sf::Image _digger13;
    sf::Image _digger14;
    sf::Image _digger15;
    sf::Image _digger16;


    sf::Sprite _nouveau_sprite;
    sf::Sprite _charger_sprite;
    sf::Sprite _enregistrer_sprite;
    sf::Sprite _editer_sprite;
    sf::Sprite _son_sprite;
    sf::Sprite _notSon_sprite;
    sf::Sprite _jouer_sprite;
    sf::Sprite _quitter_sprite;
    sf::Sprite _anglais_sprite;
    sf::Sprite _francais_sprite;
    sf::Sprite _background_sprite;
    sf::Sprite _digger_sprite;
    sf::Sprite _bombe_sprite;
    sf::Sprite _tuile_sprite;
    sf::Sprite _bonus_sprite;
    sf::Sprite _exit_sprite;
    sf::Sprite _start_sprite;
    sf::Sprite _vide_sprite;
    sf::Sprite _option_sprite;
    sf::Sprite _menu_sprite;
    sf::Sprite _bestScore_sprite;
    sf::Sprite _quitte_inGame;

    sf::Font _font;

    sf::String titre;
    sf::String affiche_Bonus;
    sf::String affiche_Score;
    sf::String _vie_player;
    sf::String _abandon;
    sf::String jouer;
    sf::String quitter;
    sf::String nom;
    sf::String score;
    sf::String langue;
    sf::String meilleursScore;

    sf::SoundBuffer Buffer;
    sf::Sound::Status status;
    sf::Sound sound;

    sf::SoundBuffer bonus;
    sf::Sound::Status bonus_status;
    sf::Sound bonusSound;

        // Button Editeur
    sf::String _editer;
    sf::String _prendre_Bomb;
    sf::String _prendre_Bonus;
    sf::String _selectionner;
    sf::String _enregistrer;
    sf::String _nouveau;
    sf::String _chargerNiveau;
    sf::String _fichierExistant;
    std::vector<std::string>m_fichierRecent;
    sf::String _nomFichier;

    sf::String m;
    sf::String g;

    bool isThemColor;

    std::string _nomDuFichier;

    bool isBonusSelecting;
    bool isBombSelecting;
    bool isInLevelEditing;

    Editeur *m_editeur;
    int compteur;
    int compteurDig;
    float a;

private:

    // PICTURE & SPRITE
    bool loadPicture(const std::string name, sf::Image &picture);
    bool loadSprite(const std::string name, sf::Image &picture, sf::Sprite &sprite);
    bool loadSprite(const std::string name, sf::Image &picture, sf::Sprite &sprite, const int rx, const int ry);
    void loadNamePicture();
    void loadNamePictureTheme();
    // change sprite
    void changeSprite(sf::Sprite &s, const float x, const float y);
    void changeSprite(sf::Sprite &s, const float x, const float y, const int r, const int g, const int b, const int alpha);
    void changeSprite(sf::Sprite &s, const float x, const float y, const int r, const int g, const int b, const int alpha, const float mx, const float my);

    void changeSpriteResize(sf::Sprite &s, const float x, const float y, const int r, const int g, const int b, const int alpha, const float rx, const float ry);

    // INIT SPRITE
    bool initSprite();

    // INIT TEXT
    void loadText(sf::String &s, const int x, const int y, const float size, const std::string text);

    void loadText(sf::String &s, const int x, const int y, const float size, const std::string text, const sf::Font &f);

    void loadText(sf::String &s, const int x, const int y, const float size, const std::string text, const int r, const int g, const int b);

    void loadText(sf::String &s, const int x, const int y, const float size, const std::string text, const sf::Font &f, const int r, const int g, const int b);

    void loadText(sf::String &s, const int x, const int y, const std::string text);

    // Focus
    bool onTheSprite(const sf::Sprite &s, const int x, const int y) const;
    bool onTheText(const sf::String &s, const int x, const int y) const;


    // MON BAC À SABLE

public:
    void Test();
private:
    sf::Event _event;

    int _previousScreen;
    int _screen;
    bool _refresh;

    // ECRAN MENU
    void initMenu();
    void displayMenu();
    void eventMenu();

    // ECRAN JEU
    void initGame();
    void displayGame();
    void eventGame();
    
    bool eventTime();
    void eventSound();
    
    void displaySound();
    void displayPlateau();

    void removeNeighbour();

    bool onTheDiggerSOUTH();
    bool onTheDiggerNORTH();
    bool onTheDiggerWEST();
    bool onTheDiggerEAST();
    bool onTheDiggerDIAG_SOUTH_EAST();
    bool onTheDiggerDIAG_SOUTH_WEST();
    bool onTheDiggerDIAG_NORTH_WEST();
    bool onTheDiggerDIAG_NORTH_EAST();

    bool diggerEvent();

    // OPTION
    void initOption();
    void displayOption();
    void eventOption();


    // EVENT
    bool detectNewEvent();
};
#endif /* defined(__THE_PURU__GameView__) */
