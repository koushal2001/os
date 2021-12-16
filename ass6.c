#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t wrt;

int readCount = 0;
int k = 1;

void *writer(void *wno)
{
    while (1)
    {
        printf("Writer %d wants to write\n", *((int *)wno));
        sem_wait(&wrt);
        printf("Writer %d is writing. Value of k is now: %d\n", *((int *)wno), ++k);
        sleep(rand() % 4);
        sem_post(&wrt);
        printf("Writer %d has finished writing.\n", *((int *)wno));
        sleep(1);
    }
}

void *reader(void *rno)
{
    while (1)
    {
        printf("Reader %d wants to read\n", *((int *)rno));
        pthread_mutex_lock(&mutex);
        readCount++;
        if (readCount == 1)
            sem_wait(&wrt);
        pthread_mutex_unlock(&mutex);
        printf("Reader %d is reading. Value of k: %d\n", *((int *)rno), k);
        sleep(rand() % 4);
        pthread_mutex_lock(&mutex);
        readCount--;
        if (readCount == 0)
            sem_post(&wrt);
        pthread_mutex_unlock(&mutex);
        printf("Reader %d has finished reading.\n", *((int *)rno));
        sleep(1);
    }
}

int main()
{
    int res;
    pthread_t readers[5], writers[5];
    res = pthread_mutex_init(&mutex, NULL);
    if (res != 0)
    {
        printf("Mutex Initialization failed.\n");
        exit(EXIT_FAILURE);
    }
    res = sem_init(&wrt, 0, 1);
    if (res != 0)
    {
        printf("Mutex initialization failed\n");
        exit(EXIT_FAILURE);
    }

    int a[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        res = pthread_create(&writers[i], NULL, (void *)writer, (void *)&a[i]);
        if (res != 0)
        {
            printf("Thread creation failed.\n");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }

    for (int i = 0; i < 5; i++)
    {
        res = pthread_create(&readers[i], NULL, (void *)reader, (void *)&a[i]);
        if (res != 0)
        {
            printf("Thread creation failed\n");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }

    for (int i = 0; i < 5; i++)
    {
        res = pthread_join(readers[i], NULL);
        if (res != 0)
        {
            printf("Thread join failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        res = pthread_join(writers[i], NULL);
        if (res != 0)
        {
            printf("Thread join failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}