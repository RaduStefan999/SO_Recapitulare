#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "sys/wait.h"
#include "errno.h"

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
        printf("eroare la deschidere canal\n");
        exit(7);
    }

    if (canal_1_0 == -1)
    {
        printf("eroare la deschidere canal\n");
        exit(7);
    }

    pid_t pid_0, pid_1;

    pid_0 = fork();

    if (pid_0 == -1)
    {
        printf("Eroare la fork \n");
        exit(8);
    }

    if (pid_0 != 0)
    {
        /* Parinte */

        pid_1 = fork();

        if (pid_1 == -1)
        {
            printf("Eroare la fork \n");
            exit(9);
        }

        if (pid_1 != 0)
        {
            /* Parinte */

            int cod_exit_p1;

            wait(&cod_exit_p1);

            char output_data[100];

            if (read(canal_1_0, output_data, 100) == -1)
            {
                printf("Eroare la read \n");
                exit(10);
            }

            printf("%s", output_data);
        }
        else
        {
            /* Copil - prg_P1.c */

            int cod_exit_p2;

            wait(&cod_exit_p2);

            if (execl("prg_P1", "P1", "canal_2_1", "canal_1_0", NULL) == -1)
            {
                printf("Eroare la exec \n");
                exit(13);
            }
        }
    }
    else
    {
        /* Copil - prg_P2.c */

        if (write(canal_0_2, data, 100) == -1)
        {
            printf("Eroare la write \n");
            exit(11);
        }

        if (execl("prg_P2", "P2", "canal_0_2", "canal_2_1", NULL) == -1)
        {
            printf("Eroare la exec \n");
            exit(12);
        }

        close(canal_0_2);
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
        if (errno == EEXIST)
        {
            printf("canalul deja exista \n");
        }
        else
        {
            printf("eroare la creeare canal \n");
            exit(4);
        }
    }
    if (mkfifo("canal_2_1", 0600) == -1)
    {
        if (errno == EEXIST)
        {
            printf("canalul deja exista \n");
        }
        else
        {
            printf("eroare la creeare canal \n");
            exit(5);
        }
    }
    if (mkfifo("canal_1_0", 0600) == -1)
    {
        if (errno == EEXIST)
        {
            printf("canalul deja exista \n");
        }
        else
        {
            printf("eroare la creeare canal \n");
            exit(6);
        }
    }
}