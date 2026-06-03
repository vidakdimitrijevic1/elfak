#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h> 

int niz[20];
pthread_mutex_t muxDole;
pthread_mutex_t muxGore;

void* dodajDole(void* arg)
{
    while(true)
    {
        pthread_mutex_lock(&muxDole);
        int poz = rand() % 10;
        int num = rand() % 100;
        niz[poz] = num;
        printf("Nit N1 je na poz %d upisala broj %d\n", poz, num);
        for(int i = 0; i < 20; i++)
        {
            printf("%d ", niz[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&muxDole);
        sleep(2);
    }
}

void* dodajGore(void* arg)
{
    while(true)
    {
        pthread_mutex_lock(&muxGore);
        int poz = rand() % 10 + 10;
        int num = rand() % 100;
        niz[poz] = num;
        printf("Nit N2 je na poz %d upisala broj %d\n", poz, num);
        for(int i = 0; i < 20; i++)
        {
            printf("%d ", niz[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&muxGore);
        sleep(4);
    }
}

void* dodajCeo(void* arg)
{
    while(true)
    {
        pthread_mutex_lock(&muxDole);
        pthread_mutex_lock(&muxGore);
        int poz = rand() % 20;
        int num = rand() % 100;
        niz[poz] = num;
        printf("Nit N3 je na poz %d upisala broj %d\n", poz, num);
        for(int i = 0; i < 20; i++)
        {
            printf("%d ", niz[i]);
        }
        printf("\n");
        pthread_mutex_unlock(&muxGore);
        pthread_mutex_unlock(&muxDole);
        sleep(8);
    }
}

void main(int argc, char* argv[])
{
    srand(time(NULL));

    pthread_t niti[3];

    pthread_mutex_init(&muxDole, NULL);
    pthread_mutex_init(&muxGore, NULL);

    for(int i = 0; i < 20; i++)
    {
        niz[i] = 0;
    }

    pthread_create(&niti[0], NULL, dodajDole, NULL);
    pthread_create(&niti[1], NULL, dodajGore, NULL);
    pthread_create(&niti[2], NULL, dodajCeo, NULL);

    for(int i = 0; i < 3; i++)
    {
        pthread_join(niti[i], NULL);
    }

    pthread_mutex_destroy(&muxDole);
    pthread_mutex_destroy(&muxGore);
}