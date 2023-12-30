#pragma once
#include <map>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>

#include "control/keys.hpp"

namespace gola
{
    struct keyboard_t
    {
        using action_type = keys::key_action_t;
        using call_type   = std::function<void()>;
        using handle_type = action_type;
        
        bool shift_pressed = false;
        bool ctrl_pressed  = false;
        
        std::map<keys::key_t, bool>      held;
        std::map<action_type, call_type> subscriptions;
        
        void on_event(const sf::Event& event)
        {
            if ((event.type != sf::Event::KeyPressed) && (event.type != sf::Event::KeyReleased)) return;
            
            keys::key_t key = keys::from_event(event);
            held[key] = (event.type == sf::Event::KeyPressed);
            
            if ((event.key.code == sf::Keyboard::LControl) || (event.key.code == sf::Keyboard::RControl)) ctrl_pressed  = (event.type == sf::Event::KeyPressed);
            if ((event.key.code == sf::Keyboard::LShift)   || (event.key.code == sf::Keyboard::RShift))   shift_pressed = (event.type == sf::Event::KeyPressed);
            
            keys::special_t special    = keys::no_special;
            if (shift_pressed) special = keys::shift;
            if (ctrl_pressed)  special = keys::ctrl;
            keys::key_action_t action{(event.type == sf::Event::KeyPressed), key, special};
            
            if (subscriptions.find(action) == subscriptions.end()) return;
            auto& fn = subscriptions.at(action);
            fn();
        }
        
        void remove(const handle_type& key)
        {
            subscriptions.erase(key);
        }
        
        void clear()
        {
            held.clear();
            subscriptions.clear();
        }
        
        bool is_held(const keys::key_t& key)
        {
            return held[key];
        }
        
        template <typename func_t>
        handle_type subscribe(const action_type& key, const func_t& func)
        {
            if (subscriptions.find(key) != subscriptions.end())
            {
                throw std::runtime_error("Attempted to over-subscribe key " + key.to_string());
            }
            subscriptions.insert({key, call_type(func)});
            return key;
        }
    };
}