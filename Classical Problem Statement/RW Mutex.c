#include <stdio.h>
#include <pthread.h>

pthread_mutex_t db_mutex;
pthread_mutex_t x_mutex;
int readerCount = 0;

void *reader(void *arg)
{
    pthread_mutex_lock(&x_mutex);
    readerCount++;
    if (readerCount == 1)
    {
        pthread_mutex_lock(&db_mutex);
    }
    pthread_mutex_unlock(&x_mutex);

    printf("Reader %ld entered db\n", (long)arg);
    printf("Reader %ld is reading...\n", (long)arg);

    pthread_mutex_lock(&x_mutex);
    readerCount--;
    if (readerCount == 0)
    {
        pthread_mutex_unlock(&db_mutex);
    }
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

void *writer(void *arg)
{
    pthread_mutex_lock(&db_mutex);
    printf("Writer %ld entered db\n", (long)arg);
    printf("Writer %ld is writing...\n", (long)arg);
    printf("Writer %ld exited from db\n", (long)arg);
    pthread_mutex_unlock(&db_mutex);

    pthread_exit(NULL);
}

int main()
{
    pthread_t readers[5], writers[5];
    pthread_mutex_init(&db_mutex, NULL);
    pthread_mutex_init(&x_mutex, NULL);

    for (long i = 0; i < 5; i++)
    {
        pthread_create(&readers[i], NULL, reader, (void *)i);
        pthread_create(&writers[i], NULL, writer, (void *)i);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&db_mutex);
    pthread_mutex_destroy(&x_mutex);

    return 0;
}
