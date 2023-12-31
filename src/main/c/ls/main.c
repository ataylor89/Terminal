#include "ls.h"
#include <stdio.h>

int main(int argc, char** argv)
{
    DirectoryList* dl;
    char* filename;

    switch (argc)
    {
        case 1:
            filename = ".";
            break;
        case 2:
            filename = argv[1];
            break;
        default:
            printf("Usage: %s [path]\n", argv[0]);
            return 0;
    }
    
    if ((dl = get_directory_list(filename)) == NULL)
    {
        fprintf(stderr, "Error getting directory list for %s\n", filename);
        return 1;
    }

    sort_directory_list(dl);

    format_directory_list(dl);

    fwrite(dl->buf, 1, dl->length, stdout);

    return 0;
}