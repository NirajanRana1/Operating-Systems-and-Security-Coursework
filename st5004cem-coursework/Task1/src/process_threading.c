#include <stdio.h>
#include <pthread.h>

// This function is the work done by each thread.
void *work(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d is doing work\n", id);
    return NULL;
}

int main() {
    pthread_t t[3];
    int id[3] = {1, 2, 3};

    // Create 3 threads.
    for (int i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, work, &id[i]);

    // Wait until all threads finish.
    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);

    printf("All threads finished\n");
    return 0;
}