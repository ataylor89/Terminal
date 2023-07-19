#include "Util.h"
#include "commands/Cd.h"
#include <filesystem>

Cd::Cd(std::string& user_input, Window* window) : Command(user_input, window)
{
    text_view = window->get_text_view();
    settings = window->get_settings();
}

void Cd::preprocess(std::string& path)
{
    if (path[0] == '~')
    {
        path.erase(0, 1);
        path = settings->get_user_directory() + path;
    }
}

void Cd::exec()
{
    std::vector<std::string> args;

    args = split(user_input, " ", 2);

    if (args.size() == 2)
    {
        preprocess(args[1]);

        if (std::filesystem::is_directory(args[1]))
        {
            if (args[1][0] == '/')
            {
                std::filesystem::current_path(args[1]);
            }

            else
            {
                std::filesystem::current_path(std::filesystem::current_path() /= args[1]);
            }
        }

        else
        {
            text_view->append("\nTerminal: The given path is not a directory.");
        }
    }

    text_view->append("\n");
    text_view->append_prefix();
}