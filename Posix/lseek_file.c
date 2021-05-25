#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main ()
{
    int fd = open("problema3.txt", O_RDONLY | O_CREAT, 0600);

    char buffer[100];

    read(fd, buffer, 5);

    buffer[5] = '\0';
    printf("%s \n", buffer);

    lseek(fd, 1, SEEK_SET);

    read(fd, buffer, 5);

    buffer[5] = '\0';
    printf("%s \n", buffer);

    lseek(fd, -5, SEEK_END);

    read(fd, buffer, 5);

    buffer[5] = '\0';
    printf("%s \n", buffer);


    return 0;
}