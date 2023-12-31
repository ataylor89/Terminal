#include "gui/TextView.h"

TextView::TextView(Settings* settings, Parser* parser)
{
    this->settings = settings;
    this->parser = parser;

    set_editable(true);
    set_wrap_mode(Gtk::WrapMode::WORD_CHAR);
    set_top_margin(5);
    set_left_margin(5);
    set_bottom_margin(5);
    set_right_margin(5);
    set_name("TextView");

    auto buffer = Gtk::TextBuffer::create();
    string prefix = settings->get_prefix();
    buffer->set_text(prefix);
    set_buffer(buffer);

    auto controller = Gtk::EventControllerKey::create();
    controller->signal_key_pressed().connect(
        sigc::mem_fun(*this, &TextView::on_key_pressed), false);
    add_controller(controller);

    auto context = get_style_context();
    auto provider = Gtk::CssProvider::create();
    auto file = Gio::File::create_for_path("src/main/cpp/gui/Stylesheet.css");
    provider->load_from_file(file);
    context->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void TextView::clear()
{
    auto buffer = get_buffer();
    string prefix = settings->get_prefix();
    buffer->set_text(prefix);
}

void TextView::append(string text)
{
    auto buffer = get_buffer();
    buffer->insert_at_cursor(text);

    auto cursor = buffer->get_insert();
    scroll_to(cursor, 0.01);
}

void TextView::append(char* text, int length)
{
    auto buffer = get_buffer();
    buffer->insert_at_cursor(text, text + length);

    auto cursor = buffer->get_insert();
    scroll_to(cursor, 0.01);
}

void TextView::append_prefix()
{
    auto buffer = get_buffer();
    string prefix = settings->get_prefix();
    buffer->insert_at_cursor(prefix);

    auto cursor = buffer->get_insert();
    scroll_to(cursor, 0.01);
}

bool TextView::on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state)
{
    if (keyval == GDK_KEY_Return)
    {
        const string prefix = settings->get_prefix();
        const int len = prefix.length();

        auto buffer = get_buffer();
        auto cursor = buffer->get_insert();
        auto end = buffer->get_iter_at_mark(cursor);
        auto start = end;

        while (start.get_char() != '\n' && start != buffer->begin())
        {
            start--;
        }

        start.forward_chars(start == buffer->begin() ? len : len + 1);

        string user_input = buffer->get_text(start, end);

        Command* cmd = parser->parse(user_input);
        cmd->exec();

        return true;
    }
    else if (keyval == GDK_KEY_BackSpace)
    {
        const string prefix = settings->get_prefix();
        const int len = prefix.length();

        auto buffer = get_buffer();
        auto cursor = buffer->get_insert();
        auto iter = buffer->get_iter_at_mark(cursor);
        iter.backward_chars(len);

        if (iter == buffer->begin())
        {
            return true;
        }

        iter.backward_chars(1);

        if (iter.get_char() == '\n')
        {
            return true;
        }
    }
    return false;
}