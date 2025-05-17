#include "DropdownSelector.hpp"
#include "graphics.hpp"
using namespace genv;

DropdownSelector::DropdownSelector(int x, int y, int sx, int sy, const std::vector<std::string>& options, int max_visible_items)
    : Widget(x, y, sx, sy), _options(options), _selected_index(0), _is_open(false) ,
      _max_visible_items(max_visible_items), _scroll_offset(0) {}

void DropdownSelector::draw() {
    gout << move_to(_x, _y) << color(255, 255, 255) << box(_size_x, _size_y);
    gout << move_to(_x + 2, _y + 2) << color(0, 0, 0) << box(_size_x - 4, _size_y - 4);

    if (!_options.empty()) {
        gout << move_to(_x + 5, _y + (_size_y - gout.cascent()) / 2 + gout.cascent())
             << color(75, 0, 130) << text(_options[_selected_index]);
    }

    int tx = _x + _size_x - 15;
    int ty = _y + (_size_y / 2) - 2;
    gout << move_to(tx, ty)
         << color(255, 255, 255)
         << line(10, 0) << line(-5, 6) << line(-5, -6);

    if (_is_open) {
        int visible_items = std::min(_max_visible_items, static_cast<int>(_options.size()) - _scroll_offset);
        for (int i = 0; i < visible_items; i++) {
            int item_y = _y + _size_y + i * _size_y;
            int option_index = _scroll_offset + i;

            gout << move_to(_x, item_y) << color(200, 200, 200) << box(_size_x, _size_y);

            if (option_index < _options.size()) {
                gout << move_to(_x + 5, item_y + (_size_y - gout.cascent()) / 2 + gout.cascent())
                     << color(75, 0, 130) << text(_options[option_index]);
            }
        }
    }
}

void DropdownSelector::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        if (is_selected(ev.pos_x, ev.pos_y)) {
            _is_open = !_is_open;
        }
        else if (_is_open) {
            int item_height = _size_y;
            int menu_y_start = _y + _size_y;
            int menu_y_end = menu_y_start + _max_visible_items * item_height;
            if (ev.pos_x >= _x && ev.pos_x <= _x + _size_x && ev.pos_y >= menu_y_start && ev.pos_y <= menu_y_end) {
                int clicked_index = (ev.pos_y - menu_y_start) / item_height;
                int actual_index = _scroll_offset + clicked_index;
                if (actual_index >= 0 && actual_index < static_cast<int>(_options.size())) {
                    _selected_index = actual_index;
                    _is_open = false;
                }
            } else {
                _is_open = false;
            }
        }
    }

    if (_is_open && ev.type == ev_mouse) {
        if (ev.button == btn_wheelup && _scroll_offset > 0) {
            _scroll_offset--;
        }
        if (ev.button == btn_wheeldown &&
            _scroll_offset + _max_visible_items < static_cast<int>(_options.size())) {
            _scroll_offset++;
        }
    }

    if (ev.type == ev_key) {
        if (ev.keycode == key_up && _selected_index > 0) {
            _selected_index--;
            if (_selected_index < _scroll_offset) _scroll_offset--;
            _is_open = true;
        } else if (ev.keycode == key_down && _selected_index < static_cast<int>(_options.size()) - 1) {
            _selected_index++;
            if (_selected_index >= _scroll_offset + _max_visible_items) _scroll_offset++;
            _is_open = true;
        } else if (ev.keycode == key_enter) {
            _is_open = false;
        }
    }
}

std::string DropdownSelector::get_value() const {
    return _options.empty() ? "" : _options[_selected_index];
}

void DropdownSelector::add_option(const std::string& option) {
    _options.push_back(option);
}

void DropdownSelector::remove_last_option() {
    if (!_options.empty()) {
        _options.pop_back();
        if (_selected_index >= static_cast<int>(_options.size())) {
            _selected_index = std::max(0, static_cast<int>(_options.size()) - 1);
        }
        if (_scroll_offset + _max_visible_items > static_cast<int>(_options.size())) {
            _scroll_offset = std::max(0, static_cast<int>(_options.size()) - _max_visible_items);
        }
    }
}
