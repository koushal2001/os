#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 10
#define MAX_ITEMS 10

sem_t full;
sem_t empty;
int queue[MAX];
int head = 0, tail = 0;
pthread_mutex_t mutex;

void printQueue() {
    if (head == tail)
        printf("Queue is empty.");
    else {
        printf("Queue: ");
        if (tail >= head) {
            for (int i = head; i < tail; i++)
                printf("%d ", queue[i]);
        }
        else {
            for(int i = head; i < MAX-1; i++)
                printf("%d ", queue[i]);
            for(int i = 0; i < tail; i++)
                printf("%d ", queue[i]);	
        }
        printf("\n");
    }
}

void* producer(void* pno) {
    while (1) {
    int item;
    
    item = rand() % 10;
    sem_wait(&empty);
    
    pthread_mutex_lock(&mutex);
    sleep(rand() % 8);
    queue[tail] = item;
    printf("Producer %d produced item %d\n", *((int*)pno), queue[tail]);
    tail = (tail + 1) % MAX_ITEMS;
    printQueue();
    pthread_mutex_unlock(&mutex);
    
    sem_post(&full);
    }
}

void* consumer(void* cno) {
    while(1) {
    sem_wait(&full);
    
    pthread_mutex_lock(&mutex);
    sleep(rand() % 5);
    int item = queue[head];
    printf("Consumer %d consumed item %d.\n", *((int*)cno), item);
    head = (head + 1) % MAX_ITEMS;
    printQueue();
    pthread_mutex_unlock(&mutex);

    sem_post(&empty);
    }
}

int main() {
    int res;

    pthread_t pros[MAX], cons[MAX];

    res = sem_init(&full, 0, 0);
    if (res != 0) {
        perror("Semaphore initialization failed.\n");
        exit(EXIT_FAILURE);
    }

    res = sem_init(&empty, 0, MAX);
    if (res != 0) {
        perror("Semaphore initialization failed\n");
        exit(EXIT_FAILURE);
    }

    res = pthread_mutex_init(&mutex, NULL);
    if (res != 0) {
        perror("Mutex initialization failed.\n");
        exit(EXIT_FAILURE);
    }

    int p, c;
    printf("Enter number of producers: ");
    scanf("%d", &p);
    printf("Enter number of consumers: ");
    scanf("%d", &c);

    int a[MAX] = {1,2,3,4,5,6,7,8,9,10};
    
    for (int i = 0; i < p; i++) {
        res = pthread_create(&pros[i], NULL, (void*)producer, (void*)&a[i]);
        if (res != 0) {
            perror("Thread creation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < c; i++) {
        res = pthread_create(&cons[i], NULL, (void*)consumer, (void*)&a[i]);
        if (res != 0) {
            perror("Thread creation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < p; i++) {
        res = pthread_join(pros[i], NULL);
        if (res != 0) {
            perror("Thread join failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < c; i++) {
        res = pthread_join(cons[i], NULL);
        if (res != 0) {
            perror("Thread join failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
