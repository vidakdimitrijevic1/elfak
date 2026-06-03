#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <wait.h>

union semun {
    int val;
};

void main(int argc, char* argv[])
{
    FILE* fileA;
    FILE* fileB;
    FILE* fileC;

    char recenica[100];

    struct sembuf sem_lock = {0, -1, 0};
    struct sembuf sem_unlock = {0, 1, 0};

    int muxid = semget((key_t)111, 1, 0666 | IPC_CREAT);
    int aid = semget((key_t)222, 1, 0666 | IPC_CREAT);
    int bid = semget((key_t)333, 1, 0666 | IPC_CREAT);

    int ret;

    union semun semopts;
    semopts.val = 1;
    semctl(muxid, 0, SETVAL, semopts);
    semopts.val = 1;
    semctl(aid, 0, SETVAL, semopts);
    semopts.val = 0;
    semctl(bid, 0, SETVAL, semopts);

    if(fork() == 0)
    {
        //proc a
        muxid = semget((key_t)111, 1, 0666 | IPC_CREAT);
        aid = semget((key_t)222, 1, 0666 | IPC_CREAT);
        bid = semget((key_t)333, 1, 0666 | IPC_CREAT);
        fileA = fopen("fileA.txt", "r");
        while(fgets(recenica, sizeof(recenica), fileA) != NULL)
        {
            semop(aid, &sem_lock, 1);
            semop(muxid, &sem_lock, 1);
            fileC = fopen("fileC.txt", "a");
            fprintf(fileC, "%s", recenica);
            fclose(fileC);
            semop(muxid, &sem_unlock, 1);
            semop(bid, &sem_unlock, 1);
        }
        fclose(fileA);

        exit(0);
    }
    else
    {
        //proc b
        muxid = semget((key_t)111, 1, 0666 | IPC_CREAT);
        aid = semget((key_t)222, 1, 0666 | IPC_CREAT);
        bid = semget((key_t)333, 1, 0666 | IPC_CREAT);
        fileB = fopen("fileB.txt", "r");
        while(fgets(recenica, sizeof(recenica), fileB) != NULL)
        {
            semop(bid, &sem_lock, 1);
            semop(muxid, &sem_lock, 1);
            fileC = fopen("fileC.txt", "a");
            fprintf(fileC, "%s", recenica);
            fclose(fileC);
            semop(muxid, &sem_unlock, 1);
            semop(aid, &sem_unlock, 1);
        }
        fclose(fileB);
        
        wait(&ret);

        semctl(111, 0, IPC_RMID, 0);
        semctl(222, 0, IPC_RMID, 0);
        semctl(333, 0, IPC_RMID, 0);
    }
}