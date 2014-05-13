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
    void draw();
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
    
    sf::RenderWindow *m_window;
    
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
    
    
    
private:
    
    // PICTURE & SPRITE
    bool loadPicture(const std::string name, sf::Image &picture);
    bool loadSprite(const std::string name, sf::Image &picture, sf::Sprite &sprite);
    bool loadSpriteResize(const std::string name, sf::Image &picture, sf::Sprite &sprite, const int rx, const int ry);
    void loadNamePicture();
    
    // INIT SPRITE
    bool initSprite();

};
#endif /* defined(__THE_PURU__GameView__) */
