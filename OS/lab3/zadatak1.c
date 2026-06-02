#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define n 5

sem_t sems[4];
char recenica[n][10] = {"Ovo", "je", "test", "za", "semafore."};

void* stampaj(void* arg)
{
    int pom = *((int*)arg);
    if(pom > 1)
    {
        sem_wait(&sems[pom - 2]);
    }

    printf("%s ", recenica[pom - 1]);
    if(pom == 5)
    {
        printf("\n");
    }

    if(pom < 5)
    {
        sem_post(&sems[pom - 1]);
    }
}

void main(int argc, char* argv[])
{
    
    pthread_t niti[5];
    int pom[n];

    for (int i = 0; i < 4; i++)
    {
        sem_init(&sems[i], 0, 1);
    }

    for(int i = 0; i < n; i++)
    {
        pom[i] = i + 1;
        pthread_create(&niti[i], NULL, stampaj, (void*)&pom[i]);
    }

    for(int i = 0; i < n; i++)
    {
        pthread_join(niti[i], NULL);
    }

    for(int i = 0; i < 4; i++)
    {
        sem_destroy(&sems[i]);
    }
}