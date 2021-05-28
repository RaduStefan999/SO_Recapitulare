#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "sys/wait.h"

void readData(char data[], char* file_name);
void createFifoFiles();

int main (int argc, char* argv[])
{
    /* Read data */

    char data[100];

    readData(data, argv[1]);


    /* Chanel comunication */

    createFifoFiles();

    int canal_0_2 = open("canal_0_2", O_RDWR);
    int canal_1_0 = open("canal_1_0", O_RDWR);

    if (canal_0_2 == -1)
    {
        printf("eroare la deschidere canal");
        exit(7);
    }

    if (canal_1_0 == -1)
    {
        printf("eroare la deschidere canal");
        exit(7);
    }

    pid_t pid_0, pid_1;

    pid_0 = fork();

    if (pid_0 != 0)
    {
        /* Parinte */

        int cod_exit_p1;
        int cod_exit_p2;

        wait(&cod_exit_p1);
        wait(&cod_exit_p2);

        char output_data[100];

        read(canal_1_0, output_data, 100);

        printf("%s", output_data);

    }
    else
    {
        pid_1 = fork();

        if (pid_1 != 0)
        {
            /* Copil - prg_P2.c */

            write(canal_0_2, data, 100);

            execl("prg_P2", "P2", "canal_0_2", "canal_2_1", NULL);

            close(canal_0_2);

        }
        else
        {
            /* Nepot - prg_P1.c */

            int cod_exit_p2;

            wait(&cod_exit_p2);

            execl("prg_P1", "P1", "canal_2_1", "canal_1_0", NULL);
        }


    }

    return 0;
}

void readData(char data[], char* file_name)
{
    int fd_input = open(file_name, O_RDWR);

    if (fd_input == -1)
    {
        printf("eroare la deschidere a fisirului");
        exit(2);
    }

    int read_size = read(fd_input, data, 100);

    if (read_size == -1)
    {
        printf("eroare la citire");
        exit(3);
    }

    data[read_size] = '\0';

    close(fd_input);
}

void createFifoFiles ()
{
    if (mkfifo("canal_0_2", 0600) == -1)
    {
        printf("eroare la creeare canal");
        //exit(4);
    }
    if (mkfifo("canal_2_1", 0600) == -1)
    {
        printf("eroare la creeare canal");
        //exit(5);
    }
    if (mkfifo("canal_1_0", 0600) == -1)
    {
        printf("eroare la creeare canal");
        //exit(6);
    }
}