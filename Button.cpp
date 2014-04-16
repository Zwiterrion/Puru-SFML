//
//  Sprite.cpp
//  Puru
//
//  Created by Etienne on 15/04/2014.
//  Copyright (c) 2014 Etienne. All rights reserved.
//

#include "Button.h"

Button::Button()
{
    chargemenent();
}
bool Button::init(const std::string &ImageFile)
{
    return m_button_image.LoadFromFile(ImageFile);
}
sf::Sprite Button::getSprite() const
{
    return m_button_sprite;
}
Button::~Button()
{}
void Button::chargemenent()
{
    if(init("startButton.png")){
        m_button_image.LoadFromFile("startButton.png");
        m_button_sprite.SetImage(m_button_image);
    }
}