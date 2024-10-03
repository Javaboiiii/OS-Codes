#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1)
    {
        // Think
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); // Simulate thinking

        // Pick up forks
        if (id % 2 == 0) { // Even philosophers pick up left fork first
            sem_wait(&forks[left_fork]);
            sem_wait(&forks[right_fork]);
        } else { // Odd philosophers pick up right fork first
            sem_wait(&forks[right_fork]);
            sem_wait(&forks[left_fork]);
        }

        // Eat
        printf("Philosopher %d is eating.\n", id);
        sleep(1); // Simulate eating

        // Put down forks
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
    }
}

int main()
{
    // Initialize semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        int *id = malloc(sizeof(int)); // Dynamically allocate memory for id
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, id);
    }

    // Join philosopher threads (this will not actually happen due to the infinite loop)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&forks[i]);
    }

    return 0;
}
