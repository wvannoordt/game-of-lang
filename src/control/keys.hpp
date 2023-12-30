#pragma once

#include <SFML/Graphics.hpp>

namespace gola::keys
{
    enum special_t
    {
        no_special = 0,
        shift = 1,
        ctrl = 2
    };
    
    struct key_t
    {
        char principal;
        
        bool operator < (const key_t& rhs) const
        {
            return principal < rhs.principal;
        }
    };
    
    static key_t a('a');
    static key_t b('b');
    static key_t c('c');
    static key_t d('d');
    static key_t e('e');
    static key_t f('f');
    static key_t g('g');
    static key_t h('h');
    static key_t i('i');
    static key_t j('j');
    static key_t k('k');
    static key_t l('l');
    static key_t m('m');
    static key_t n('n');
    static key_t o('o');
    static key_t p('p');
    static key_t q('q');
    static key_t r('r');
    static key_t s('s');
    static key_t t('t');
    static key_t u('u');
    static key_t v('v');
    static key_t w('w');
    static key_t x('x');
    static key_t y('y');
    static key_t z('z');
    //
    static key_t n0('0');
    static key_t n1('1');
    static key_t n2('2');
    static key_t n3('3');
    static key_t n4('4');
    static key_t n5('5');
    static key_t n6('6');
    static key_t n7('7');
    static key_t n8('8');
    static key_t n9('9');
    //
    static key_t esc('E');
    static key_t tab('T');
    static key_t del('D');
    static key_t enter('N');
    static key_t nil('@');
    //
    static key_t down_arrow('K');
    static key_t uppr_arrow('I');
    static key_t left_arrow('J');
    static key_t rght_arrow('L');
    
    key_t from_event(const sf::Event& event)
    {
        key_t output = nil;
        switch (event.key.code)
        {
            case sf::Keyboard::A:      { output = a;     break;}
            case sf::Keyboard::B:      { output = b;     break;}
            case sf::Keyboard::C:      { output = c;     break;}
            case sf::Keyboard::D:      { output = d;     break;}
            case sf::Keyboard::E:      { output = e;     break;}
            case sf::Keyboard::F:      { output = f;     break;}
            case sf::Keyboard::G:      { output = g;     break;}
            case sf::Keyboard::H:      { output = h;     break;}
            case sf::Keyboard::I:      { output = i;     break;}
            case sf::Keyboard::J:      { output = j;     break;}
            case sf::Keyboard::K:      { output = k;     break;}
            case sf::Keyboard::L:      { output = l;     break;}
            case sf::Keyboard::M:      { output = m;     break;}
            case sf::Keyboard::N:      { output = n;     break;}
            case sf::Keyboard::O:      { output = o;     break;}
            case sf::Keyboard::P:      { output = p;     break;}
            case sf::Keyboard::Q:      { output = q;     break;}
            case sf::Keyboard::R:      { output = r;     break;}
            case sf::Keyboard::S:      { output = s;     break;}
            case sf::Keyboard::T:      { output = t;     break;}
            case sf::Keyboard::U:      { output = u;     break;}
            case sf::Keyboard::V:      { output = v;     break;}
            case sf::Keyboard::W:      { output = w;     break;}
            case sf::Keyboard::X:      { output = x;     break;}
            case sf::Keyboard::Y:      { output = y;     break;}
            case sf::Keyboard::Z:      { output = z;     break;}
            case sf::Keyboard::Num0:   { output = n0;    break;}
            case sf::Keyboard::Num1:   { output = n1;    break;}
            case sf::Keyboard::Num2:   { output = n2;    break;}
            case sf::Keyboard::Num3:   { output = n3;    break;}
            case sf::Keyboard::Num4:   { output = n4;    break;}
            case sf::Keyboard::Num5:   { output = n5;    break;}
            case sf::Keyboard::Num6:   { output = n6;    break;}
            case sf::Keyboard::Num7:   { output = n7;    break;}
            case sf::Keyboard::Num8:   { output = n8;    break;}
            case sf::Keyboard::Num9:   { output = n9;    break;}
            case sf::Keyboard::Escape: { output = esc;   break;}
            case sf::Keyboard::Tab:    { output = tab;   break;}
            case sf::Keyboard::Delete: { output = del;   break;}
            case sf::Keyboard::Enter:  { output = enter; break;}
            //
            case sf::Keyboard::Up:    { output = uppr_arrow; break;}
            case sf::Keyboard::Down:  { output = down_arrow; break;}
            case sf::Keyboard::Left:  { output = left_arrow; break;}
            case sf::Keyboard::Right: { output = rght_arrow; break;}
        }
        
        return output;
    }
    
    struct key_action_t
    {
        bool is_press;
        key_t key;
        special_t special;
        
        std::size_t get_val() const
        {
            return std::size_t(key.principal) + 300*std::size_t(special) + 300*5*std::size_t(is_press);
        }
        
        std::string to_string() const
        {
            std::string output;
            output += is_press?"[press] ":"[release] ";
            if (special == ctrl)  output += "ctrl + ";
            if (special == shift) output += "shift + ";
            output += key.principal;
            return output;
        }
        
        bool operator < (const key_action_t& rhs) const
        {
            return get_val() < rhs.get_val();
        }
    };
    
    key_action_t on_press(const key_t& key, const special_t& special = no_special)
    {
        return key_action_t{true, key, special};
    }
    
    key_action_t on_release(const key_t& key)
    {
        return key_action_t{false, key, no_special};
    }
}