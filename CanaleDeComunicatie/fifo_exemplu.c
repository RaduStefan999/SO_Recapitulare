#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"


int main ()
{
    mkfifo("test", 0600);

    return 0;
}