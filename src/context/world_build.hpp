#pragma once

#include "assets/asset_pool.hpp"
#include "context/Igame_context.hpp"

namespace gola
{
    struct world_builder_t : public Igame_context_t
    {
        sf::Vector2f cam_coords;   //world coordinates
        sf::Vector2f mouse_coords; //Relative to the screen
        
        const asset_pool_t<sf::Font>*    fonts;
        const asset_pool_t<sf::Texture>* textures;
        
        world_builder_t(const asset_pool_t<sf::Font>& fonts_in, const asset_pool_t<sf::Texture>& textures_in)
        {
            fonts      = &fonts_in;
            textures   = &textures_in;
            cam_coords = {0.0f, 0.0f};
        }
        
        void subscribe(keyboard_t& keyboard, mouse_t& mouse) override final
        {
            this->add_event(mouse.subscribe(mouse_event::move, [&](const float& x, const float& y) { mouse_coords = sf::Vector2f(x, y); }));
        }
        
        sf::Transform get_transform() const
        {
            sf::Transform output = sf::Transform::Identity;
            
            return output;
        }
        
        void draw(sf::RenderWindow& window) override final
        {
            const auto transform = this->get_transform();
            
            
        }
    };
}