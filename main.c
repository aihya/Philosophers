#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define N   3

pthread_t       tid[N];
pthread_mutex_t mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

void*   routine(void* args)
{
    pthread_mutex_lock(&mutex);
    printf("thread %d locked mutex\n", *(int*)args);
    // sleep(1);
    printf("thread %d runs...\n", *(int*)args);
    // printf("thread %d unlocked mutex \n", *(int*)args);
    // pthread_mutex_unlock(&mutex);
    return (NULL);
}

int     main()
{
    int         i;

    i = -1;
    while (++i < N)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&tid[i], NULL, routine, a);
    }
    i = -1;
    while (++i < N)
    {
        pthread_join(tid[i], NULL);
    }
    return (0);
}