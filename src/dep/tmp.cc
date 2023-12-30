#include <print.h>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

enum sprite_dir
{
    dir_dw = 0,
    dir_rg = 1,
    dir_up = 2,
    dir_lf = 3
};

struct sprite_t
{
    sf::Texture texture;
    sf::Sprite sprite;
    constexpr static int wid = 12;
    constexpr static int hei = 16;
    constexpr static int frame_count = 4;
    int ifrm = 0;
    sprite_dir idir = dir_dw;
    sprite_t(const std::string& im_name)
    {
        texture.loadFromFile(im_name);
        sprite.setTexture(texture);
        this->cycle();
        sprite.setScale(10.0f, 10.0f);
    }
    
    void setpos(float x, float y)
    {
        sprite.setPosition(x, y);
    }
    
    void addpos(float dx, float dy)
    {
        sprite.move(dx, dy);
    }
    
    void cycle()
    {
        ifrm++;
        ifrm = ifrm%(4*frame_count);
        sprite.setTextureRect(sf::IntRect(wid*(ifrm/(frame_count)), hei*int(idir), wid, hei));
    }
    
    void set_dir(const sprite_dir& di) { idir = di; }
};

int main(int argc, char** argv)
{
    const int width  = 2560;
    const int height = 1360;
    sprite_t guy("charac.png");
    sf::RenderWindow main_window(sf::VideoMode(width, height), "Sprite test");
    main_window.display();
    bool ctrl_pressed = false;
    bool w_pressed = false;
    bool a_pressed = false;
    bool s_pressed = false;
    bool d_pressed = false;
    
    bool debug_info = false;
    
    double framerate = 60.0;
    std::size_t frame_count = 0;
    double time_s = 0;
    while(main_window.isOpen())
    {
        auto pre = std::chrono::system_clock::now();
        sf::Event event;
        while(main_window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::LControl) ctrl_pressed = true;
                if (event.key.code == sf::Keyboard::W) w_pressed = true;
                if (event.key.code == sf::Keyboard::A) a_pressed = true;
                if (event.key.code == sf::Keyboard::S) s_pressed = true;
                if (event.key.code == sf::Keyboard::D) d_pressed = true;
                
                if (event.key.code == sf::Keyboard::I) debug_info = !debug_info;
            }
            
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::LControl) ctrl_pressed = false;
                if (event.key.code == sf::Keyboard::W) w_pressed = false;
                if (event.key.code == sf::Keyboard::A) a_pressed = false;
                if (event.key.code == sf::Keyboard::S) s_pressed = false;
                if (event.key.code == sf::Keyboard::D) d_pressed = false;
            }
            
            if (w_pressed && ctrl_pressed) main_window.close();
        }
        
        float speed = 10.0;
        if (w_pressed)
        {
            guy.addpos(0.0, -speed);
            guy.set_dir(dir_up);
        }
        
        if (a_pressed)
        {
            guy.addpos(-speed, 0.0);
            guy.set_dir(dir_lf);
        }
        
        if (s_pressed)
        {
            guy.addpos(0.0, speed);
            guy.set_dir(dir_dw);
        }
        
        if (d_pressed)
        {
            guy.addpos(speed, 0.0);
            guy.set_dir(dir_rg);
        }
        
        if (a_pressed || s_pressed || w_pressed || d_pressed)
        {
            guy.cycle();
        }
        
        main_window.clear({155, 155, 155, 255});
        
        //draw
        main_window.draw(guy.sprite);
        
        
        main_window.display();
        
        auto post = std::chrono::system_clock::now();
        std::size_t dur_us = std::chrono::duration_cast<std::chrono::microseconds>(post-pre).count();
        std::size_t required_dur_us = 1000000.0/framerate;
        if (dur_us < required_dur_us)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(required_dur_us - dur_us));
        }
        auto post2 = std::chrono::system_clock::now();
        std::size_t dur2_us = std::chrono::duration_cast<std::chrono::microseconds>(post2-pre).count();
        ++frame_count;
        time_s += dur2_us/1000000.0;
        std::string title = "Sprite test";
        if (debug_info) title +=  (" - " + std::to_string(double(frame_count)/(time_s)) + " fps, load: " + std::to_string(100.0*double(dur_us)/(dur_us+required_dur_us)) + "%");
        main_window.setTitle(title);
    }
    
    return 0;
}