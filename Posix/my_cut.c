#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BLOCK_SIZE 4096

char input_file[100];
char delimitor[100];

int main (int argc, char * argv[])
{
    if (argc < 2)
    {
        printf("no file found");
        exit(0);
    }
    else
    {
        strcpy(input_file, argv[1]);

        int i = 2;

        while (i < argc)
        {
            if (strcmp(argv[i], "-d") == 0)
            {
                i++;

                if (i < argc)
                {
                    strcpy(delimitor, argv[i]);
                }
            }
            
            i++;
        }
    }

    char input_buffer[100];

    int fd_i = open(input_file, O_RDONLY);

    int read_size = read(fd_i, input_buffer, BLOCK_SIZE);

    while (read_size != 0 && read_size != -1)
    {
        char * pointer = strstr(input_buffer, delimitor);

        while (pointer != NULL)
        {
            *pointer = '\0';

            printf("%s \n", input_buffer);

            strcpy(input_buffer, pointer + strlen(delimitor));

            pointer = strchr(input_buffer, '\n');

            strcpy(input_buffer, pointer + 1);

            pointer = strstr(input_buffer, delimitor);
        }
        

        read_size = read(fd_i, input_buffer, BLOCK_SIZE);
    }
    

    return 0;
}