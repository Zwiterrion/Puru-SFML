#ifndef Pong_GameView_h
#define Pong_GameView_h

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameModel;

class GameView
{
public:
    GameView(int w, int h, int bpp);
    ~GameView();
    
    void setModel(GameModel *model);
    void draw();
    bool treatEvents();
    
private:
    GameModel * m_model;
    int _w, _h;
    
    sf::RenderWindow * m_window;
    sf::Image _background_image;
    sf::Image _ball_image;
    sf::Image _bat_image;
    sf::Image _bat_right_image;
    
    sf::Sprite _background_sprite;
    sf::Sprite _ball_sprite;
    sf::Sprite _bat_sprite;
    sf::Sprite _bat_right_sprite;
    
};


#endif
