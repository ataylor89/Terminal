#ifndef WINDOW_H
#define WINDOW_H

#include "Settings.h"
#include "util/ForwardDeclarations.h"
#include "parser/Parser.h"
#include "gui/TextView.h"
#include <gtkmm.h>

class Window : public Gtk::Window
{
public:
    Window();
    Settings* get_settings();
    Parser* get_parser();
    TextView* get_text_view();
private:
    Gtk::Box vbox;
    Gtk::ScrolledWindow scrolled_window;
    Settings* settings;
    Parser* parser;
    TextView* text_view;
};

#endif