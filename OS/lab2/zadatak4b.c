#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void main(int argc, char* argv[])
{
    char *prom[10];
    prom[0] = (char*)malloc(10*sizeof(char));
    strcpy(prom[0], "zad4a");
    for (int i = 1; i < argc; i++)
    {
        prom[i] = (char*)malloc(10*sizeof(char));
        strcpy(prom[i], argv[i]);
    }
    execv("./zad4a", prom);
    return;
}