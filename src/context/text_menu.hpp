#pragma once

#include <string>

#include <SFML/Graphics.hpp>

namespace gola
{
    struct text_menu_t : Igame_context_t
    {
        const sf::Font& font;
        std::vector<sf::Text> options;
        std::vector<std::function<void()>> actions;
        int selected;
        float px_size, px_spacing;
        sf::Color unselected_color;
        sf::Color selected_color;
        
        text_menu_t(const sf::Font& font_in)
        : font{font_in}
        {
            selected = 0;
            px_size = 90;
            px_spacing = 15;
            
            this->unselected_color = {0,  0,  0,  255};
            this->selected_color   = {155,0,  0,  255};
        }
        
        template <typename func_t>
        void add_option(const std::string& str, const func_t& call)
        {
            sf::Text txt;
            txt.setFont(font);
            txt.setString(str);
            txt.setCharacterSize(px_size);
            txt.setPosition(px_spacing, px_spacing+options.size()*(px_size + px_spacing));
            txt.setFillColor(unselected_color);
            if (options.size() == 0) txt.setFillColor(selected_color);
            options.push_back(txt);
            actions.emplace_back(call);
        }
        
        
        void subscribe(keyboard_t& keyboard, mouse_t& mouse) override final
        {
            this->add_event(keyboard.subscribe(keys::on_press(keys::enter),      [&]() { actions[selected](); }));
            this->add_event(keyboard.subscribe(keys::on_press(keys::uppr_arrow), [&]() { this->cycle(-1); }));
            this->add_event(keyboard.subscribe(keys::on_press(keys::down_arrow), [&]() { this->cycle(1);  }));
            
            this->add_event(mouse.subscribe(mouse_event::move, [&](const float& x, const float& y)
            {
                int i = 0;
                for (const auto& txt: options)
                {
                    if (txt.getGlobalBounds().contains(x, y))
                    {
                        options[selected].setFillColor(unselected_color);
                        selected = i;
                        options[selected].setFillColor(selected_color);
                    }
                    ++i;
                }
            }));
            
            this->add_event(mouse.subscribe(mouse_event::left_click, [&](const float& x, const float& y)
            {
                actions[selected]();
            }));
        }
        
        void cycle(int dir)
        {
            options[selected].setFillColor(unselected_color);
            selected += dir;
            if (selected < 0) selected = this->size()-1;
            if (selected >= this->size()) selected = 0;
            options[selected].setFillColor(selected_color);
        }
        
        int size()
        {
            return options.size();
        }
        
        void draw(sf::RenderWindow& window) override final
        {
            for (const auto& item: options)
            {
                window.draw(item);
            }
        }
        
        
    };
}