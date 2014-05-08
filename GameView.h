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
    static void rejouer();
    static void affichageScore();
    static void retourMenu();
    std::string afficheBonus() const;
    std::string afficheScore() const;
    std::string viePlayer() const;
    static void perteVie();
    static void changementLevel();
    static void plusDeVie();

private:
    GameModel *m_model;
    std::vector<sf::Sprite*> images;
    
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
    
    sf::Font _font;
    sf::String titre;
    sf::String affiche_Bonus;
    sf::String affiche_Score;
    sf::String _vie_player;
    sf::String _abandon;
    sf::String jouer;
    sf::String quitter;
    
    

};
#endif /* defined(__THE_PURU__GameView__) */
