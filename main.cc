#include <print.h>
#include "gola.hpp"

int main(int argc, char** argv)
{
    gola::asset_pool_t<sf::Font>    font_pool("resources/fonts");
    gola::asset_pool_t<sf::Texture> txtr_pool("resources/textures");
    gola::main_window_t window(font_pool, txtr_pool);
    
    window.run();
    
    return 0;
}