#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    printf("Hello World!\n");
    FILE* cpuinfo;
    cpuinfo = popen("lscpu -e --all", "r");

    pclose(cpuinfo);
    return 0;
}
