#include "ButtonWidget.hpp"
#include "graphics.hpp"
using namespace genv;

ButtonWidget::ButtonWidget(int x, int y, int sx, int sy, const std::string& label, std::function<void()> on_click)
    : Widget(x, y, sx, sy), label(label), on_click(on_click) {}

void ButtonWidget::draw() {
    gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y);
    gout << move_to(_x + 2, _y + 2) << color(0, 0, 0) << box(_size_x - 4, _size_y - 4);
    gout << move_to(_x + (_size_x - gout.twidth(label)) / 2, _y + (_size_y - gout.cascent()) / 2 + gout.cascent())
         << color(75, 0, 130) << text(label);
}

void ButtonWidget::handle(genv::event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left && is_selected(ev.pos_x, ev.pos_y)) {
        on_click();
    }
    if (ev.type == ev_key && ev.keycode == key_enter) {
        on_click();
    }
}

std::string ButtonWidget::get_value() const {
    return label;
}
