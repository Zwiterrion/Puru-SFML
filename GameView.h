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

class GameView{

public:
    GameView(int h, int w, int bpp);
    virtual ~GameView();
    void setModel(GameModel *model);
      void affichageScore();
    std::string afficheBonus() const;
    std::string afficheScore() const;
    std::string viePlayer() const;

private:
    GameModel *m_model;
    std::vector<sf::Sprite*> images;
    std::string s_nom;
    bool isEnable;
    std::vector<std::string>m_s;
    
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
    
private: // SFML
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
    
    sf::Font _font;
    sf::String titre;
    sf::String affiche_Bonus;
    sf::String affiche_Score;
    sf::String _vie_player;
    sf::String _abandon;
    sf::String jouer;
    sf::String quitter;
    sf::String nom;
    
    sf::SoundBuffer Buffer;
    sf::Sound::Status status;
    sf::Sound sound;
    
    sf::SoundBuffer bonus;
    sf::Sound::Status bonus_status;
    sf::Sound bonusSound;

};
#endif /* defined(__THE_PURU__GameView__) */
