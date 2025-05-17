#ifndef DROPDOWNSELECTOR_HPP_INCLUDED
#define DROPDOWNSELECTOR_HPP_INCLUDED

#include "widgets.hpp"
#include <vector>
#include <string>

class DropdownSelector : public Widget {
protected:
    std::vector<std::string> _options;
    int _selected_index;
    bool _is_open;
    int _max_visible_items;
    int _scroll_offset;

public:

    DropdownSelector(int x, int y, int sx, int sy, const std::vector<std::string>& options, int max_visible_items);
    void draw() override;
    void handle(genv::event ev) override;
    std::string get_value() const override;
    void add_option(const std::string& option);
    void remove_last_option();
};

#endif // DROPDOWNSELECTOR_HPP_INCLUDED
