#include "Shell.h"

Shell::Shell(Window* window) 
{
    this->window = window;
}

void Shell::exec(const std::string command)
{
    Parser* parser;
    Command* cmd;
    TextArea* text_area;

    parser = window->get_parser();
    cmd = parser->parse(command);
    
    if (cmd == NULL)
    {
        text_area = window->get_text_area();
        text_area->append("\nShell: command not found: " + command + "\n");
        text_area->append_prefix();
    }
    else
    {
        cmd->exec();
    }
}