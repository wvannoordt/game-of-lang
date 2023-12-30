#pragma once

#include <SFML/Graphics.hpp>

namespace gola
{
    namespace mouse_event
    {
        enum mouse_action_t
        {
            left_click,
            rght_click,
            left_release,
            rght_release,
            left_drag,
            rght_drag,
            move
        };
    }
    
    struct mouse_t
    {
        using handle_type = mouse_action_t;
        void on_event(const sf::Event& event)
        {
            
        }
        
        void remove(const handle_type& handle)
        {
            
        }
    };
}