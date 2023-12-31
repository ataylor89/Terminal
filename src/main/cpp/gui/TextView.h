#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include "Settings.h"
#include "parser/Parser.h"
#include <gtkmm.h>

class TextView : public Gtk::TextView
{
public:
    TextView(Settings* settings, Parser* parser);
    void clear();
    void append(string text);
    void append(char* text, int length);
    void append_prefix();
private:
    bool on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);
    Settings* settings;
    Parser* parser;
};

#endif