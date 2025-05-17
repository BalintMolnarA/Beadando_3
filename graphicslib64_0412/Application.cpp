#include "Application.hpp"
#include "graphics.hpp"
using namespace genv;

Application::Application() : focus(-1), in_menu(true) {
    gout.open(600, 400);
    std::vector<std::string> options = {"Gep ellen", "Ket jatekos"};
    widgets.push_back(new DropdownSelector(100, 180, 200, 40, options, 2));
    widgets.push_back(new ButtonWidget(300, 180, 200, 40, "Start", []() {}));
    focus = 0;
}

Application::~Application() {
    for (Widget* w : widgets) delete w;
}

void Application::draw_instructions() {
    if (in_menu) {
        gout << move_to(10, 15) << color(75, 0, 130) << text("Valassz jatekmodot es nyomd meg a Start gombot!");
    }
}

void Application::handle_event(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        focus = -1;
        for (size_t i = 0; i < widgets.size(); ++i) {
            if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                focus = i;
                widgets[i]->handle(ev);
                break;
            }
        }
        if (in_menu && focus == -1) {
            widgets[0]->handle(ev);
        }
    }
    if (focus != -1 && ev.type != ev_mouse) {
        widgets[focus]->handle(ev);
    }
}

void Application::run() {
    event ev;
    while (gin >> ev && !(ev.type == ev_key && ev.keycode == key_escape)) {
        handle_event(ev);
        gout << move_to(0, 0) << color(0, 0, 0) << box(600, 400);
        draw_instructions();
        for (Widget* w : widgets) w->draw();
        gout << refresh;
    }
}
