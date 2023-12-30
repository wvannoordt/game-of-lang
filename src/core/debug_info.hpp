#pragma once

#include <map>
#include <vector>

namespace gola
{
    struct debug_info_t
    {
        int px_size;
        int px_spacing;
        const sf::Font& font;
        std::map<std::string, sf::Text> contents;
        std::vector<std::string> keys;
        
        debug_info_t(const sf::Font& font_in) : font{font_in}
        {
            px_size    = 60;
            px_spacing = 5;
        }
        
        void compute_positions()
        {
            float i = px_spacing;
            float j = px_spacing;
            for (const auto& p: keys)
            {
                auto& txt = contents.at(p);
                txt.setPosition(i, j);
                j += (px_spacing + px_size);
            }
        }
        
        void add_prop(const std::string& key, const std::string& content)
        {
            contents[key].setFont(font);
            contents[key].setCharacterSize(px_size);
            keys.push_back(key);
            compute_positions();
            set_prop(key, content);
        }
        
        void set_prop(const std::string& key, const std::string& content)
        {
            auto& txt = contents.at(key);
            txt.setString(key + ": " + content);
        }
        
        void draw(sf::RenderWindow& window) const
        {
            int i = px_spacing;
            for (const auto& p: contents)
            {
                window.draw(p.second);
            }
        }
    };
}