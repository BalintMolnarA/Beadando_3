#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"
#include <string>
#include <vector>

class Widget {
protected:


    int _x, _y, _size_x, _size_y;


public:


    Widget(int x, int y, int sx, int sy);
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual void draw() = 0;
    virtual void handle(genv::event ev) = 0;
    virtual std::string get_value() const = 0;

};

#endif // WIDGETS_HPP_INCLUDED
