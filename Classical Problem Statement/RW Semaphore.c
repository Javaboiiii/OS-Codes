#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Include this header for the sleep function

sem_t db;
sem_t x;
int readerCount = 0;

void *reader(void *arg) {
    long id = (long)arg;

    sem_wait(&x);
    readerCount++;
    printf("Reader %ld entered db\n", id);
    if (readerCount == 1) {
        sem_wait(&db);
    }
    sem_post(&x);

    printf("Reader %ld is reading...\n", id);
    // Simulate reading process
    sleep(1);

    sem_wait(&x);
    readerCount--;
    printf("Reader %ld exited from db\n", id);
    if (readerCount == 0) {
        sem_post(&db);
    }
    sem_post(&x);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    long id = (long)arg;

    sem_wait(&db);
    printf("Writer %ld entered db\n", id);
    printf("Writer %ld is writing...\n", id);
    // Simulate writing process
    sleep(1);
    sem_post(&db);
    printf("Writer %ld exited from db\n", id);

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[5], writers[5];
    sem_init(&db, 0, 1);
    sem_init(&x, 0, 1);

    // Allocate memory for thread arguments
    long reader_ids[5], writer_ids[5];
    for (long i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        writer_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void *)reader_ids[i]);
        pthread_create(&writers[i], NULL, writer, (void *)writer_ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&db);
    sem_destroy(&x);

    return 0;
}
