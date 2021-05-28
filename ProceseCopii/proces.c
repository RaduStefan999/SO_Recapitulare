#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t proces_pid = fork();

    if (proces_pid != 0)
    {
        /* Parinte */

        int cod_terminare;

        wait(&cod_terminare);

        printf("Parintele imi afiseaza asta iar fiul a scos codul asta %d", WEXITSTATUS(cod_terminare));


    }
    else
    {
        /* Copil */

        printf("Fiul imi afiseaza asta \n");

        return(5);
    }

    return 0;
}

