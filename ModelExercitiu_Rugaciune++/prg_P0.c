#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "sys/wait.h"

int main (int argc, char* argv[])
{
    /* Read data */

    char data[100];

    int fd_input = open(argv[1], O_RDWR);

    int read_size = read(fd_input, data, 100);

    data[read_size] = '\0';

    /* Chanel comunication */

    mkfifo("canal_0_2", 0600);
    mkfifo("canal_2_1", 0600);
    mkfifo("canal_1_0", 0600);

    int canal_0_2 = open("canal_0_2", O_RDWR);
    int canal_1_0 = open("canal_1_0", O_RDWR);

    pid_t pid_0, pid_1;

    pid_0 = fork();

    if (pid_0 != 0)
    {
        /* Parinte */

        pid_1 = fork();

        if (pid_1 != 0)
        {
            /* Parinte */

            int cod_exit_p1;

            wait(&cod_exit_p1);

            char output_data[100];

            read(canal_1_0, output_data, 100);

            printf("%s", output_data);
        }
        else
        {
            /* Copil - prg_P1.c */

            int cod_exit_p2;

            wait(&cod_exit_p2);

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

    return 0;
}