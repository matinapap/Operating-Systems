#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_COUNT 6

// Shared counters
int counter = 0, counter1 = 0, counter2 = 0;

// Mutexes for protecting counters
pthread_mutex_t m0, m1, m2;

// Semaphores for synchronizing thread execution order
sem_t s[THREAD_COUNT];

void *thread_func_1(void *arg) {
    int id = *(int *)arg;
    int i;

    // Wait for semaphore signal
    sem_wait(&s[id]);

    printf("ID = %d\n", id);
    printf("A.%d\n", id);

    // Signal the next thread in Group 1
    if (id < 2) {
        sem_post(&s[id + 1]); // Signal the next thread in Group 1
    } else {
        sem_post(&s[3]); // Signal the first thread in Group 2
    }

    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&m1);
        counter1++;
        pthread_mutex_unlock(&m1);
    }

    printf("B.%d\n", id);

    // Signal the next thread in Group 1
    if (id < 2) {
        sem_post(&s[id + 1]); // Signal the next thread in Group 1
    } else {
        sem_post(&s[3]); // Signal the first thread in Group 2
    }

    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&m1);
        counter1++;
        pthread_mutex_unlock(&m1);
    }

    printf("C.%d\n", id);

    // Signal the next thread in Group 1
    if (id < 2) {
        sem_post(&s[id + 1]); // Signal the next thread in Group 1
    } else {
        sem_post(&s[3]); // Signal the first thread in Group 2
    }

    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&m0);
        counter++;
        pthread_mutex_unlock(&m0);
    }

    return NULL;
}

void *thread_func_2(void *arg) {
    int id = *(int *)arg;
    int i;

    // Wait for semaphore signal
    sem_wait(&s[id]);

    printf("ID = %d\n", id);
    printf("A.%d\n", id);

    // Signal the next thread in Group 2
    if (id < 5) {
        sem_post(&s[id + 1]); // Signal the next thread in Group 2
    } else {
        sem_post(&s[0]); // Signal the first thread in Group 1
    }

    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&m2);
        counter2++;
        pthread_mutex_unlock(&m2);
    }

    printf("B.%d\n", id);

    // Signal the next thread in Group 2
    if (id < 5) {
        sem_post(&s[id + 1]); // Signal the next thread in Group 2
    } else {
        sem_post(&s[0]); // Signal the first thread in Group 1
    }

    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&m0);
        counter++;
        pthread_mutex_unlock(&m0);
    }

    printf("C.%d\n", id);

    // Signal the next thread in Group 2
    if (id < 5) {
        sem_post(&s[id + 1]); // Signal the next thread in Group 2
    } else {
        sem_post(&s[0]); // Signal the first thread in Group 1
    }

    for (i = 0; i < 10000000; i++) {
        pthread_mutex_lock(&m2);
        counter2++;
        pthread_mutex_unlock(&m2);
    }

    return NULL;
}


int main() {
    pthread_t threads[6];
    int thread_ids[6];
    int i;

    // Initialize semaphores
    for (i = 0; i < 6; i++) {
        sem_init(&s[i], 0, (i == 0) ? 1 : 0); // Start with semaphore 0 unlocked
    }

    // Initialize mutexes
    pthread_mutex_init(&m0, NULL);
    pthread_mutex_init(&m1, NULL);
    pthread_mutex_init(&m2, NULL);

    // Create threads
    for (i = 0; i < 6; i++) {
        thread_ids[i] = i;
        if (i < 3) {
            pthread_create(&threads[i], NULL, thread_func_1, &thread_ids[i]);
        } else {
            pthread_create(&threads[i], NULL, thread_func_2, &thread_ids[i]);
        }
    }

    // Wait for threads to finish
    for (i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print final counter values
    printf("Final counter: %d\n", counter);
    printf("Final counter1: %d\n", counter1);
    printf("Final counter2: %d\n", counter2);

    // Destroy semaphores and mutexes
    for (i = 0; i < 6; i++) {
        sem_destroy(&s[i]);
    }
    pthread_mutex_destroy(&m0);
    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);

    return 0;
}