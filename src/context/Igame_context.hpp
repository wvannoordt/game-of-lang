#pragma once

#include "control/keyboard.hpp"
#include "control/mouse.hpp"

namespace gola
{
    struct Igame_context_t
    {
        std::vector<typename keyboard_t::handle_type>     keyboard_handles;
        std::vector<typename mouse_t::mouse_handle_type>  mouse_handles;
        std::vector<typename mouse_t::scroll_handle_type> scroll_handles;

        void unsubscribe(keyboard_t& keyboard, mouse_t& mouse)
        {
            for (const auto& handle: this->keyboard_handles)  keyboard.remove(handle);
            for (const auto& handle: this->mouse_handles)     mouse.remove(handle);
            for (const auto& handle: this->scroll_handles)    mouse.remove(handle);
        }
        
        virtual void subscribe(keyboard_t&, mouse_t&) = 0;
        virtual void draw(sf::RenderWindow&)          = 0;
    };
}