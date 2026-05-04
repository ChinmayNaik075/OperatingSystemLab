#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// semaphores
sem_t empty, full, mutex;

// control flags
int produce_flag = 0;
int consume_flag = 0;

void* producer(void* arg)
{
    int item = 1;
    while (1)
    {
        if (produce_flag)
        {
            sem_wait(&empty);
            sem_wait(&mutex);

            buffer[in] = item;
            printf("Producer produced: Item %d\n", item);
            in = (in + 1) % BUFFER_SIZE;
            item++;

            sem_post(&mutex);
            sem_post(&full);

            produce_flag = 0; // reset
        }
    }
}

void* consumer(void* arg)
{
    int item;
    while (1)
    {
        if (consume_flag)
        {
            if (sem_trywait(&full) == 0)
            {
                sem_wait(&mutex);

                item = buffer[out];
                printf("Consumer consumed: Item %d\n", item);
                out = (out + 1) % BUFFER_SIZE;

                sem_post(&mutex);
                sem_post(&empty);
            }
            else
            {
                printf("Buffer is empty!\n");
            }

            consume_flag = 0; // reset
        }
    }
}

int main()
{
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    int choice;

    while (1)
    {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            produce_flag = 1;
        else if (choice == 2)
            consume_flag = 1;
        else
            break;
    }

    return 0;
}