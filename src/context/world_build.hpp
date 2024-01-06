#pragma once

#include "context/Igame_context.hpp"

namespace gola
{
    struct world_builder_t : public Igame_context_t
    {
        void subscribe(keyboard_t& keyboard, mouse_t& mouse) override final
        {
            
        }
        
        void draw(sf::RenderWindow& window) override final
        {
            
        }
    };
}