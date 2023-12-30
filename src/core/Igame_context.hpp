#pragma once

#include "control/keyboard.hpp"
#include "control/mouse.hpp"

namespace gola
{
    struct Igame_context_t
    {
        virtual void subscribe(keyboard_t&)   = 0;
        virtual void subscribe(mouse_t&)      = 0;
        virtual void draw(sf::RenderWindow&)  = 0;
    };
}