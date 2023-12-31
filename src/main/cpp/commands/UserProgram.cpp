#include "commands/UserProgram.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

UserProgram::UserProgram(string& cmd, vector<string>& args, Window* window) 
: Command(cmd, args, window)
{
    text_view = window->get_text_view();
    settings = window->get_settings();
}

void UserProgram::exec()
{
    string path;
    int argc;

    path = settings->get_program_directory() + "/" + args[0];
    argc = args.size();

    char* argv[argc + 1];

    for (int i = 0; i < argc; i++)
    {
        argv[i] = strdup(args[i].c_str());
    }

    argv[argc] = NULL;

    text_view->append("\n");

    exec(path.c_str(), argv);

    auto buffer = text_view->get_buffer();
    auto cursor = buffer->get_insert();
    auto iter = buffer->get_iter_at_mark(cursor);
    iter.backward_char();

    if (iter.get_char() != '\n')
    {
        text_view->append("\n");
    }

    text_view->append_prefix();

    delete this;
}

void UserProgram::exec(const char* path, char** argv)
{
    int fds[2];

    pipe(fds);

    if (fork() == 0)
    {
        dup2(fds[1], fileno(stdout));
        close(fds[0]);
        execv(path, argv);
    }

    close(fds[1]);

    char program_output[256];
    int length;

    while (true)
    {
        length = read(fds[0], program_output, 256);

        if (length <= 0)
        {
            break;
        }

        text_view->append(program_output, length);
    }
}