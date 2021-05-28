#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "errno.h"
#include "sys/stat.h"
#include "sys/types.h"


int main ()
{
    //execvp("cat", comnda);
    //system("cat /etc/passwd");

    //execlp("cat", "cat", "/etc/passwd", NULL);

    /*
    char* comnda[10];

    comnda[0] = "cat";
    comnda[1] = "/etc/passwd";
    comnda[2] = NULL;

    execvp("cat", comnda);
    */

execl("/usr/bin/cat","cat","/etc/passwd",NULL);
    return 0;
}