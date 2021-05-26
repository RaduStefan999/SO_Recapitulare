#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

#include "string.h"

char input_file[100];

int main (int argc, char * argv[])
{
    if (argc != 2)
    {
        scanf("%s", input_file);
    }
    else
    {
        strcpy(input_file, argv[1]);
    }

    int fd_i = open(input_file, O_RDWR);

    char ch;

    char replace = '-';

    int nr_citite = read(fd_i, &ch, 1);

    struct flock lacat;

    lacat.l_type = F_WRLCK;
    lacat.l_whence = SEEK_CUR;
    lacat.l_start = 0;
    lacat.l_len = 1;

    while (nr_citite != -1 && nr_citite != 0)
    {
        if (ch == '#')
        {
            lseek(fd_i, -1, SEEK_CUR);
         
            fcntl(fd_i, F_SETLKW, &lacat);

            write(fd_i, &replace, 1);
        }

        nr_citite = read(fd_i, &ch, 1);
    }

    close(fd_i);

    return 0;
}