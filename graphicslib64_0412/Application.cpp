#include "Application.hpp"
#include "graphics.hpp"
using namespace genv;

Application::Application() : game(new JatekMester(15)), focus(-1), in_menu(true), computer_opponent(false) {
    gout.open(600, 400);
    std::vector<std::string> options = {"Gep ellen", "Ket jatekos"};
    widgets.push_back(new DropdownSelector(100, 180, 200, 40, options, 2));
    widgets.push_back(new ButtonWidget(300, 180, 200, 40, "Start", [this]() {
        DropdownSelector* ds = dynamic_cast<DropdownSelector*>(widgets[0]);
        if (ds) {
            computer_opponent = (ds->get_value() == "Gep ellen");
            start_game(computer_opponent);
        }
    }));
    focus = 0;
}

Application::~Application() {
    for (Widget* w : widgets) delete w;
    delete game;
}

void Application::start_game(bool computer) {
    in_menu = false;
    widgets.clear();
    widgets.push_back(new GameBoardWidget(150, 50, 300, 300, *game, computer));
    focus = 0;
}

void Application::reset_game() {
    delete game;
    game = new JatekMester(15);
    widgets.clear();
    widgets.push_back(new GameBoardWidget(150, 50, 300, 300, *game, computer_opponent));
    focus = 0;
}

void Application::return_to_menu() {
    in_menu = true;
    widgets.clear();
    delete game;
    game = new JatekMester(15);
    std::vector<std::string> options = {"Gep ellen", "Ket jatekos"};
    widgets.push_back(new DropdownSelector(100, 180, 200, 40, options, 2));
    widgets.push_back(new ButtonWidget(300, 180, 200, 40, "Start", [this]() {
        DropdownSelector* ds = dynamic_cast<DropdownSelector*>(widgets[0]);
        if (ds) {
            computer_opponent = (ds->get_value() == "Gep ellen");
            start_game(computer_opponent);
        }
    }));
    focus = 0;
}

void Application::draw_instructions() {
    if (in_menu) {
        gout << move_to(10, 15) << color(75, 0, 130) << text("Valassz jatekmodot es nyomd meg a Start gombot!");
    } else if (game->get_state() != JatekMester::RUNNING) {
        gout << move_to(10, 15) << color(75, 0, 130) << text("Uj jatekhoz nyomd meg az r-t, menube: m");
    } else {
        gout << move_to(10, 15) << color(75, 0, 130) << text("Kilepeshez: ESC");
    }
}

void Application::handle_event(event ev) {
    if (ev.type == ev_key && ev.keycode == 'r' && !in_menu && game->get_state() != JatekMester::RUNNING) {
        reset_game();
        return;
    }
    if (ev.type == ev_key && ev.keycode == 'm' && !in_menu && game->get_state() != JatekMester::RUNNING) {
        return_to_menu();
        return;
    }
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
