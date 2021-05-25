#include <unistd.h>
#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "string.h"

#define BLOCK_SIZE 4096

char fisier_input[100], fisier_output[100];

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Fisierul de input : \n");
        scanf("%s", fisier_input);
        printf("Fisierul de output : \n");
        scanf("%s", fisier_output);
    }
    else
    {
        strcpy(fisier_input, argv[1]);
        strcpy(fisier_output, argv[2]);
    }

    int fd_i = open(fisier_input, O_RDONLY);
    int fd_o = open(fisier_output, O_WRONLY | O_CREAT | O_TRUNC, 0600);

    char buffer[BLOCK_SIZE];
    char out_buffer[BLOCK_SIZE];

    int read_size = read(fd_i, buffer, BLOCK_SIZE);

    while (read_size != 0 && read_size != -1)
    {
        int out_size = 0;

        for (int i = 0; i < read_size; i++)
        {
            if (strchr("AEIOUaeiou", buffer[i]) == 0)
            {
                out_buffer[out_size++] = buffer[i];
            }
        }

        write(fd_o, out_buffer, out_size);
        read_size = read(fd_i, buffer, BLOCK_SIZE);
    }

    close(fd_i);
    close(fd_o);
    

    return 0;
}