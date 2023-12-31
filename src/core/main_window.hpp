#pragma once

#include <memory>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "core/frame_rate.hpp"
#include "core/debug_info.hpp"
#include "core/timer.hpp"

#include "context/Igame_context.hpp"
#include "context/text_menu.hpp"
#include "context/topdown_env.hpp"
#include "context/world_build.hpp"

#include "control/keyboard.hpp"
#include "control/mouse.hpp"

#include "assets/asset_pool.hpp"

namespace gola
{
    struct main_window_t
    {
        std::unique_ptr<sf::RenderWindow> window;
        
        keyboard_t keyboard;
        std::vector<typename keyboard_t::handle_type> keyboard_handles;
        
        mouse_t mouse;
        // std::vector<typename mouse_t::mouse_handle_type> mouse_handles;
        
        
        debug_info_t debug_info;
        frame_rate_t frame_rate;
        
        // world builder mode
        world_builder_t world_builder;
        
        bool display_debug;
        
        const asset_pool_t<sf::Font>&       all_fonts;
        const asset_pool_t<sf::Texture>&    all_textures;
        
        //Probably need to switch to better std:: pointers here
        Igame_context_t* background_context;
        Igame_context_t* current_context;
        
        text_menu_t main_menu;
        text_menu_t esc_menu;
        
        timer_t frame_timer;
        
        main_window_t(const asset_pool_t<sf::Font>& fonts_in, const asset_pool_t<sf::Texture>& txtrs_in)
        : all_fonts{fonts_in},
          all_textures{txtrs_in},
          frame_rate(60.0),
          debug_info(fonts_in["noto_mono"]),
          main_menu(fonts_in["noto_mono"]),
          esc_menu(fonts_in["noto_mono"]),
          world_builder(fonts_in, txtrs_in)
        {
            const int init_wid = sf::VideoMode::getDesktopMode().width;
            const int init_hei = sf::VideoMode::getDesktopMode().height;
            window = std::make_unique<sf::RenderWindow>(sf::VideoMode(init_wid, init_hei), "A Game of Language", sf::Style::Fullscreen);
            display_debug = false;
            
            debug_info.add_prop("framerate", "?");
            this->subscribe(keyboard);
            // this->subscribe(mouse);
            
            background_context = nullptr;
            current_context    = nullptr;
            
            esc_menu.add_option("Continue",  [&]() { this->set_context(background_context); });
            esc_menu.add_option("Main Menu", [&]() { this->set_context(&main_menu); });
            esc_menu.add_option("Exit",      [&]() { this->window->close(); });
            
            main_menu.add_option("New Game",     [&]() {  });
            main_menu.add_option("Load",         [&]() {  });
            main_menu.add_option("World Builder",[&]() { this->set_context(&world_builder); });
            main_menu.add_option("Options",      [&]() {  });
            main_menu.add_option("Exit",         [&]() { this->window->close(); });
            this->set_context(&main_menu);
        }
        
        void subscribe(keyboard_t& board)
        {
            // Note that this is permanently bound.
            this->add_event(board.subscribe(keys::on_press(keys::i, keys::ctrl), [&]() { display_debug = !display_debug; }));
            this->add_event(board.subscribe(keys::on_press(keys::esc), [&]()
            {
                if (current_context != &main_menu) { background_context = current_context; this->set_context(&esc_menu); }
            }));
        }
        
        void add_event(const keyboard_t::handle_type& handle)
        {
            this->keyboard_handles.push_back(handle);
        }
        
        void set_context(Igame_context_t* context)
        {
            if (current_context != nullptr) current_context->unsubscribe(keyboard, mouse);
            current_context = context;
            if (context != nullptr) context->subscribe(keyboard, mouse);
        }

        void render()
        {
            //Render the current scene
            // if (background_context != nullptr) background_context->draw(*window);
            if (current_context != nullptr) current_context->draw(*window);
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
                frame_timer.start();
                frame_rate.start();
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
                auto dur = frame_rate.get_pause_duration();
                std::this_thread::sleep_for(dur);
                frame_rate.stop();
                frame_timer.stop();
                if (current_context != nullptr)
                {
                    current_context->update(frame_timer.elapsed_seconds());
                }
            }
        }
    };
}