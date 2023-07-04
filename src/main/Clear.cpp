#include "Clear.h"

Clear::Clear(std::string& cmd, Window* window) : Command(cmd, window) {}

void Clear::exec()
{
    TextView* text_view = window->get_text_view();
    text_view->clear();
}