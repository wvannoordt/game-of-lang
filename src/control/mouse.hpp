#pragma once

#include <functional>

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
        
        enum scroll_action_t
        {
            scroll,
            temp
        };
    }
    
    struct mouse_t
    {
        
        using mouse_handle_type  = mouse_event::mouse_action_t;
        using scroll_handle_type = mouse_event::scroll_action_t;
        std::map<mouse_handle_type,  std::function<void(const float&, const float&)>> mouse_action_subscriptions;
        std::map<scroll_handle_type, std::function<void(const float&)>>               scroll_action_subscriptions;
        
        bool left_held = false;
        bool rght_held = false;
        float mouse_x{0.0f}, mouse_y{0.0f};
        
        void on_event(const sf::Event& event)
        {
            if ((event.type == sf::Event::MouseButtonPressed) || (event.type == sf::Event::MouseButtonReleased))
            {
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    rght_held = (event.type == sf::Event::MouseButtonPressed);
                    if (event.type == sf::Event::MouseButtonPressed)  this->execute(mouse_event::rght_click);
                    if (event.type == sf::Event::MouseButtonReleased) this->execute(mouse_event::rght_release);
                }
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    left_held = (event.type == sf::Event::MouseButtonPressed);
                    if (event.type == sf::Event::MouseButtonPressed)  this->execute(mouse_event::left_click);
                    if (event.type == sf::Event::MouseButtonReleased) this->execute(mouse_event::left_release);
                }
            }
            
            if (event.type == sf::Event::MouseMoved)
            {
                mouse_x = event.mouseMove.x;
                mouse_y = event.mouseMove.y;
                if (left_held)
                {
                    this->execute(mouse_event::left_drag);
                }
                if (rght_held)
                {
                    this->execute(mouse_event::rght_drag);
                }
                this->execute(mouse_event::move);
            }
            
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    this->execute(mouse_event::scroll, event.mouseWheelScroll.delta);
                }
            }
        }
        
        template <typename func_t>
        auto subscribe(const mouse_handle_type& key, const func_t& func)
        {
            if (mouse_action_subscriptions.find(key) != mouse_action_subscriptions.end())
                throw std::runtime_error("Attempted to over-subscribe mouse event");
            mouse_action_subscriptions[key] = func;
            return key;
        }
        
        template <typename func_t>
        auto subscribe(const scroll_handle_type& key, const func_t& func)
        {
            if (scroll_action_subscriptions.find(key) != scroll_action_subscriptions.end())
                throw std::runtime_error("Attempted to over-subscribe scroll event");
            scroll_action_subscriptions[key] = func;
            return key;
        }
        
        void execute(const mouse_handle_type& mouse_action)
        {
            if (mouse_action_subscriptions.find(mouse_action) != mouse_action_subscriptions.end())
                mouse_action_subscriptions.at(mouse_action)(mouse_x, mouse_y);
        }
        
        void execute(const scroll_handle_type& scroll_action, const float& delta)
        {
            if (scroll_action_subscriptions.find(scroll_action) != scroll_action_subscriptions.end())
                scroll_action_subscriptions.at(scroll_action)(delta);
        }
        
        void remove(const mouse_handle_type& handle)
        {
            if (mouse_action_subscriptions.find(handle) != mouse_action_subscriptions.end())
                mouse_action_subscriptions.erase(handle);
        }
        
        void remove(const scroll_handle_type& handle)
        {
            if (scroll_action_subscriptions.find(handle) != scroll_action_subscriptions.end())
                scroll_action_subscriptions.erase(handle);
        }
    };
}