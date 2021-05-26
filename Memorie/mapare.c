#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/mman.h"
#include "sys/stat.h"

#include "string.h"

int main ()
{
    int fd = open("map_exemplu.txt", O_RDWR);

    /* Dimensiune */

    struct stat sb;
    fstat(fd, &sb);

    /* Mapare */

    void * adresa = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    /* Operatii pe sir */

    char * inceput = ((char *)adresa);

    char *replace = strstr(inceput, "rima");

    *replace = '\0';
    
    char aux[100];

    strcpy(aux, inceput);
    strcat(aux, "crima");
    strcat(aux, replace + strlen("crima") - 1);
    strcpy(inceput, aux);

    printf("%s", inceput);

    /* Sincronizare */

    msync(adresa, sb.st_size, MS_ASYNC);

    close(fd);

    return 0;
}