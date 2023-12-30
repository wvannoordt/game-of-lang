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
        
        text_menu_t(const sf::Font& font_in)
        : font{font_in}
        {
            selected = 0;
            px_size = 90;
            px_spacing = 15;
        }
        
        template <typename func_t>
        void add_option(const std::string& str, const func_t& call)
        {
            sf::Text txt;
            txt.setFont(font);
            txt.setString(str);
            txt.setCharacterSize(px_size);
            txt.setPosition(px_spacing, px_spacing+options.size()*(px_size + px_spacing));
            txt.setFillColor({0,0,0,255});
            if (options.size() == 0) txt.setFillColor({155,0,0,255});
            options.push_back(txt);
            actions.emplace_back(call);
        }
        
        
        void subscribe(keyboard_t& keyboard, mouse_t& mouse) override final
        {
            this->keyboard_handles.push_back(keyboard.subscribe(keys::on_press(keys::enter),      [&]() { actions[selected](); }));
            this->keyboard_handles.push_back(keyboard.subscribe(keys::on_press(keys::uppr_arrow), [&]() { this->cycle(-1); }));
            this->keyboard_handles.push_back(keyboard.subscribe(keys::on_press(keys::down_arrow), [&]() { this->cycle(1);  }));
        }
        
        void cycle(int dir)
        {
            options[selected].setFillColor({0,0,0,255});
            selected += dir;
            if (selected < 0) selected = this->size()-1;
            if (selected >= this->size()) selected = 0;
            options[selected].setFillColor({155,0,0,255});
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