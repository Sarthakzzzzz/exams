#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t emptySlots, fullSlots;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item = 1;
    while (1) {
        sem_wait(&emptySlots);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced item %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;
        item++;

        pthread_mutex_unlock(&mutex);
        sem_post(&fullSlots);
        sleep(1);
    }
}

void* consumer(void* arg) {
    while (1) {
        sem_wait(&fullSlots);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&emptySlots);
        sleep(2);
    }
}

int main() {
    pthread_t prodThread, consThread;

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);

    return 0;
}
