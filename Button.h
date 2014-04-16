//
//  Sprite.h
//  Puru
//
//  Created by Etienne on 15/04/2014.
//  Copyright (c) 2014 Etienne. All rights reserved.
//

#ifndef __Puru__Button__
#define __Puru__Button__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button
{
    public :
    
    static bool init(const std::string& ImageFile);
    Button();
    ~Button();
    sf::Sprite getSprite() const;
    void chargemenent();
    
    private :
    static sf::Image m_button_image;
    sf::Sprite m_button_sprite;
};

#endif /* defined(__Puru__Button__) */
