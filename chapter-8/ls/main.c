#include "dirent.h"
#include "fsize.h"

int main(int argc, char const *argv[])
{
    if (argc == 1) /* default: current directory */
        fsize(".");
    else
        while (--argc > 0) 
            fsize(*++argv);
    return 0;
}


