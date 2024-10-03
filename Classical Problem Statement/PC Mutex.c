
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

pthread_mutex_t mutex_empty;
pthread_mutex_t mutex_filled;

void *producer(void *arg)
{
    int item = 1;
    while (1)
    {
        pthread_mutex_lock(&mutex_empty);

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex_filled);
        item++;
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item;
    while (1)
    {

        pthread_mutex_lock(&mutex_filled);

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex_empty);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
