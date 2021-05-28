#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "string.h"

int main (int argc, char* argv[])
{
    int fd_date_de_la_1 = open(argv[1], O_RDWR, 0600);

    char date[100];

    read(fd_date_de_la_1, date, 100);

    int i = 0;

    while (date[i] != '\0')
    {
        if (date[i] >= '0' && date[i] <= '9')
        {
            strcpy(date + i, date + i + 1);

            i--;
        }

        i++;
    }


    int fd_date_catre_0 = open(argv[2], O_RDWR, 0600);
    
    write(fd_date_catre_0, date, 100);

    close(fd_date_catre_0);
}