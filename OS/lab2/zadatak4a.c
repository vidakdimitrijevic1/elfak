#include <stdio.h>

void main(int argc, char* argv[]) 
{
    if (argc == 1)
    {
        printf("Program nema parametara\n");
        return;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }
    }
}