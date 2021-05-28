#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "sys/wait.h"
#include <string.h>

// Function to swap two numbers
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // consider the absolute value of the number
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

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

    int canal_0_2 = open("canal_0_2", O_RDWR);

    int anonim_chanel[2];

    pipe(anonim_chanel);


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

            close(anonim_chanel[1]);

            read(anonim_chanel[0], output_data, 100);

            printf("%s", output_data);
            
        }
        else
        {
            /* Copil - prg_P1.c */

            int cod_exit_p2;

            wait(&cod_exit_p2);

            char anonim_chanel_string_in[10];

            itoa(anonim_chanel[1], anonim_chanel_string_in, 10);

            execl("prg_P1", "P1", "canal_2_1", anonim_chanel_string_in, NULL);
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