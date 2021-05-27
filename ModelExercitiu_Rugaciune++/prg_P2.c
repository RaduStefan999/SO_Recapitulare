#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/types.h"

int main (int argc, char* argv[])
{
    int fd_date_de_la_0 = open(argv[1], O_RDWR, 0600);

    char date[100];

    read(fd_date_de_la_0, date, 100);

    printf("astea sunt dateles  %s", date);

    return 0;
}