#include <stdio.h>
#include <pthread.h>

int n;

void* sortiraj(void* niz)
{
    int* vrsta = (int*)niz;
    for (int i = 0; i < n - 1; i++)
    {
        int imin = i;
        for(int j = i; j < n; j++)
        {
            if(vrsta[j] < vrsta[imin])
            {
                imin = j;
            }
        }
        int pom = vrsta[i];
        vrsta[i] = vrsta[imin];
        vrsta[imin] = pom;
    }
}

void main(int argc, char* argv[])
{
    
    printf("Unesite velicinu kvadratne matrice\n");
    scanf("%d", &n);

    pthread_t niti[n];
    int mat[n][n];
    
    printf("Popunite matricu\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    for(int i = 0; i < n; i++)
    {
        int prom = i;
        pthread_create(&niti[prom], NULL, sortiraj, (void*)mat[prom]);
    }

    for(int i = 0; i < n; i++)
    {
        pthread_join(niti[i], NULL);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
        
}