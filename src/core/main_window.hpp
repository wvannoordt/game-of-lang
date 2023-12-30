#pragma once

#include <memory>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "core/frame_rate.hpp"
#include "core/debug_info.hpp"
#include "core/Igame_context.hpp"

#include "control/keyboard.hpp"
#include "control/mouse.hpp"

#include "assets/asset_pool.hpp"

namespace gola
{
    struct main_window_t
    {
        std::unique_ptr<sf::RenderWindow> window;
        
        keyboard_t keyboard;
        mouse_t mouse;
        debug_info_t debug_info;
        frame_rate_t frame_rate;
        
        bool display_debug;
        
        const asset_pool_t<sf::Font>&    all_fonts;
        
        Igame_context_t* context;
        
        main_window_t(const asset_pool_t<sf::Font>& fonts_in, const asset_pool_t<sf::Texture>& txtrs_in)
        : all_fonts{fonts_in}, all_textures{txtrs_in}, frame_rate(60.0), debug_info(fonts_in["noto_mono"])
        {
            const int init_wid = sf::VideoMode::getDesktopMode().width;
            const int init_hei = sf::VideoMode::getDesktopMode().height;
            window = std::make_unique<sf::RenderWindow>(sf::VideoMode(init_wid, init_hei), "A Game of Language", sf::Style::Fullscreen);
            display_debug = false;
            
            debug_info.add_prop("framerate", "?");
            this->subscribe(keyboard);
        }
        
        void subscribe(keyboard_t& board)
        {
            board.subscribe(keys::on_press(keys::i, keys::ctrl), [&]() { display_debug = !display_debug; });
        }

        void render()
        {
            //Render the current scene
            if (display_debug)
            {
                debug_info.set_prop("framerate", std::to_string(frame_rate.fps()) + " fps");
                debug_info.draw(*window);
            }
        }
        
        void run()
        {
            while (window->isOpen())
            {
                sf::Event event;
                // this->tick();
                while (window->pollEvent(event))
                {
                    //Main event loop
                    
                    //Update subscribable controls first
                    keyboard.on_event(event);
                    mouse.on_event(event);
                }
                
                window->clear({155, 155, 155, 255});
                this->render();
                window->display();
            }
        }
    };
}