#include "GameModel.h"
#include "GameView.h"


#include <iostream>

using namespace std;
using namespace sf;

GameView::GameView(int w, int h, int bpp): _w(w), _h(h)
{
    m_window = new RenderWindow(sf::VideoMode(w, h,bpp), "Pong en SFML", sf::Style::Close);
    
    if(!_background_image.LoadFromFile("background.png") || !_ball_image.LoadFromFile("ball.png") || !_bat_image.LoadFromFile("bat.png") || !_bat_right_image.LoadFromFile("bat.png")){
       
        _background_sprite = Sprite();
        _ball_sprite = Sprite();
        _bat_sprite = Sprite();
        _bat_right_sprite = Sprite();
    }
    else {
        _background_sprite = Sprite (_background_image);
        _background_sprite.Resize(_w, _h);
        _background_sprite.SetPosition(0,0);
        
        _bat_sprite = Sprite(_bat_image);
        _ball_sprite = Sprite(_ball_image);
        _bat_right_sprite = Sprite(_bat_right_image);
    }
    
}
void GameView::setModel(GameModel *model)
{
    m_model = model;
}
GameView::~GameView()
{
    if(m_window != NULL)
        delete m_window;
}
void GameView::draw()
{
    m_window->Clear(Color(0, 255, 255));
    m_window->Draw(_background_sprite);
        
    m_window->Draw(_ball_sprite);
    m_window->Draw(_bat_sprite);
    m_window->Draw(_bat_right_sprite);
    
    m_window->Display();
}
bool GameView::treatEvents()
{
    bool result = false;
    bool left_bat;
    if(m_window->IsOpened())
    {
        result = true;
        Event event;
        while(m_window->GetEvent(event))
        {
           
                
        }
    }
    return result;
}









