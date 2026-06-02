#include <stdio.h>
#include <unistd.h>
#include <string.h>

void main(int argc, char* argv[])
{
    char prom[30];
    printf("Unesite naziv fajla koji zelite da kopirate u tmp\n");
    scanf("%s", prom);

    execlp("cp", "cp", prom, "./tmp", NULL);
}