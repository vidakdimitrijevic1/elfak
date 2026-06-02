#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

int buff[2];
pthread_mutex_t mux;
pthread_cond_t buffFull;
pthread_cond_t buffEmpt;
bool bufferFull = false; 

void* generisi(void* arg)
{
    while(true)
    {
        pthread_mutex_lock(&mux);
        while(bufferFull)
        {
            pthread_cond_wait(&buffEmpt, &mux);
        }
        for(int i = 0; i < 2; i++)
        {
            int num = rand() % 10 + 1;
            buff[i] = num;
        }
        printf("Upisani su brojevi: %d i %d\n", buff[0], buff[1]);
        bufferFull = true;
        pthread_cond_signal(&buffFull);
        pthread_mutex_unlock(&mux);
    }
    
}

void main(int argc, char* argv[])
{
    pthread_t nit;
    pthread_mutex_init(&mux, NULL);
    pthread_cond_init(&buffFull, NULL);
    pthread_cond_init(&buffEmpt, NULL);
    pthread_create(&nit, NULL, generisi, NULL);
    while(true)
    {
        pthread_mutex_lock(&mux);
        while(!bufferFull)
        {
            pthread_cond_wait(&buffFull, &mux);
        }
        printf("Zbir je: %d\n", buff[0] + buff[1]);
        bufferFull = false;
        pthread_cond_signal(&buffEmpt);
        int sleepTime = rand() % 6;
        sleep(sleepTime);
        pthread_mutex_unlock(&mux);
    }

    pthread_mutex_destroy(&mux);
    pthread_cond_destroy(&buffFull);
    pthread_cond_destroy(&buffEmpt);
}