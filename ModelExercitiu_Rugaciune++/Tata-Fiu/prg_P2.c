#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"

void operation(char date[]);

int main (int argc, char* argv[])
{
    int fd_date_de_la_0 = open(argv[1], O_RDWR, 0600);

    if (fd_date_de_la_0 == -1)
    {
        printf("eroare la deschidere \n");
        exit(13);
    }

    char date[100];

    if (read(fd_date_de_la_0, date, 100) == -1)
    {
        printf("eroare la citire \n");
        exit(14);
    }

    operation(date);

    int fd_date_catre_1 = open(argv[2], O_RDWR, 0600);
    

    if (write(fd_date_catre_1, date, 100) == -1)
    {
        printf("eroare la scriere \n");
        exit(14);
    }

    close(fd_date_catre_1);

    return 0;
}

void operation(char date[])
{
    int i = 0;

    while (date[i] != '\0')
    {
        if (date[i] >= 'a' && date[i] <= 'z')
        {
            date[i] = date[i] - 'a' + 'A';
        }

        i++;
    }
}