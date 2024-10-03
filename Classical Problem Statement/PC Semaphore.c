#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep()

#define BUFFER_SIZE 8
#define MAX_ITEMS 20 // Maximum number of items to produce for demonstration

sem_t empty_slots;
sem_t full_slots;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
int item_count = 0; // Count of produced items for termination

void *producer(void *arg)
{
    int item = 1;

    while (item_count < MAX_ITEMS)
    {
        printf("Produced item: %d\n", item);

        sem_wait(&empty_slots);

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&full_slots);

        item++;
        item_count++;
        sleep(1); // Add sleep to slow down production for demo
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int consumed_count = 0;

    while (consumed_count < MAX_ITEMS)
    {
        sem_wait(&full_slots);

        int consumed = buffer[out];
        printf("Consumed item: %d\n", consumed);

        out = (out + 1) % BUFFER_SIZE;

        sem_post(&empty_slots);

        consumed_count++;
        sleep(1); // Add sleep to slow down consumption for demo
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t producer_thread, consumer_thread;
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    return 0;
}
