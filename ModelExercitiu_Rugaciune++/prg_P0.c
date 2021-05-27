#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"

int main (int argc, char* argv[])
{
    /* Read data */

    char data[100];

    int fd_input = open(argv[1], O_RDWR);

    read(fd_input, data, 100);

    /* Chanel comunication */

    mkfifo("canal_0_2", 0600);
    mkfifo("canal_2_1", 0600);
    mkfifo("canal_1_0", 0600);

    int canal_0_2 = open("canal_0_2", O_RDWR);

    pid_t pid_0, pid_1;

    pid_0 = fork();

    if (pid_0 != 0)
    {
        /* Parinte */

        pid_1 = fork();

        if (pid_1 != 0)
        {
            /* Parinte */
        }
        else
        {
            /* Copil - prg_P1.c */

            execl("prg_P1", "P1", "canal_2_1", "canal_1_0", NULL);
        }
    }
    else
    {
        /* Copil - prg_P2.c */

        write(canal_0_2, data, 100);

        execl("prg_P2", "P2", "canal_0_2", "canal_2_1", NULL);

        close(canal_0_2);
    }
}