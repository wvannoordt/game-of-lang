#pragma once

#include <concepts>

#include "control/keyboard.hpp"
#include "control/mouse.hpp"

namespace gola
{
    template <typename T> concept valid_handle_c
            =  std::same_as<T, typename keyboard_t::handle_type>
            || std::same_as<T, typename mouse_t::mouse_handle_type>
            || std::same_as<T, typename mouse_t::scroll_handle_type>;
    
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
        
        // template <valid_handle_c handle_t>
        template <typename handle_t>
        void add_event(const handle_t& handle)
        {
            auto& handles = *[&]() -> decltype(auto)
            {
                if      constexpr (std::same_as<handle_t, typename keyboard_t::handle_type>)
                    { return &keyboard_handles; }
                else if constexpr (std::same_as<handle_t, typename mouse_t::mouse_handle_type>)
                    { return &mouse_handles; }
                else  return &scroll_handles;
            }();
            
            handles.push_back(handle);
        }
        
        virtual void subscribe(keyboard_t&, mouse_t&) = 0;
        virtual void draw(sf::RenderWindow&)          = 0;
        
        virtual void update(const double& time_since_last) { }
    };
}