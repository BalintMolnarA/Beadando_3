#ifndef BUTTON_WIDGET_HPP_INCLUDED
#define BUTTON_WIDGET_HPP_INCLUDED

#include "widgets.hpp"
#include <functional>
#include <string>

class ButtonWidget : public Widget {
    std::string label;
    std::function<void()> on_click;

public:
    ButtonWidget(int x, int y, int sx, int sy, const std::string& label, std::function<void()> on_click);
    void draw() override;
    void handle(genv::event ev) override;
    std::string get_value() const override;
};

#endif // BUTTON_WIDGET_HPP_INCLUDED
