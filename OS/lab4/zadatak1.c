#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

#define line_size 80

void main(int argc, char* argv[])
{
    int p1[2], p2[2], pid1, pid2;

    if (pipe(p1) == -1)
    {
        printf("Greska prilikom otvaranja pipe-a 1");
        return;
    }
    if (pipe(p2) == -1)
    {
        printf("Greska prilikom otvaranja pipe-a 2");
        return;
    }

    if(pid1 = fork() != 0)
    {
        close(p1[0]);
        close(p2[0]);
        close(p2[1]);

        char recenica[line_size];

        do
        {
            fgets(recenica, line_size, stdin);
            recenica[strcspn(recenica, "\n")] = '\0';
            printf("Prvi proces je primio i salje recenicu: %s\n", recenica);
            write(p1[1], recenica, strlen(recenica) + 1);
        }
        while(strcmp(recenica, "kraj") != 0);

        printf("Prvi proces je primio: kraj\n");
        close(p1[1]);
    }
    else if(pid2 = fork() != 0)
    {
        close(p1[1]);
        close(p2[0]);

        char recenica1[line_size];

        do
        {
            read(p1[0], recenica1, line_size);
            printf("Drugi proces je primio recenicu: %s\n", recenica1);
            if(recenica1[0] >= 'a' && recenica1[0] <= 'z')
            {
                recenica1[0] = toupper(recenica1[0]); 
            }

            printf("Drugi proces salje recenicu: %s\n", recenica1);
            write(p2[1], recenica1, strlen(recenica1) + 1);
        }
        while(strcmp(recenica1, "Kraj") != 0);

        printf("Drugi proces je primio: kraj\n");
        close(p1[0]);
        close(p2[1]);
    }
    else
    {
        close(p1[0]);
        close(p1[1]);
        close(p2[1]);

        char recenica2[line_size];

        do
        {
            read(p2[0], recenica2, line_size);
            printf("Treci proces je primio recenicu: %s\n", recenica2);
            int len = strlen(recenica2);
            if(recenica2[strlen(recenica2) - 1] != '.')
            {
                recenica2[len] = '.';
                recenica2[len + 1] = '\0';
            }
            printf("Konacna recenica je: %s\n", recenica2);
        }
        while(strcmp(recenica2, "Kraj."));

        printf("Treci proces je primio: kraj\n");
        close(p2[0]);
    }
}