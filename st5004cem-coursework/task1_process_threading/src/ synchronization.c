#include <stdio.h>
#include <pthread.h>

int counter = 0;                    // Shared resource - like a printer everyone wants
pthread_mutex_t lock;               // Lock - like a key to use printer one at a time

void *work(void *arg) 
{
    int id = *(int *)arg;
    
    pthread_mutex_lock(&lock);      // Grab the key (wait if someone else has it)
    
    counter++;                      // Use shared resource safely
    printf("Thread %d: counter = %d\n", id, counter);
    
    pthread_mutex_unlock(&lock);    // Return the key for others
    
    return NULL;
}

int main() 
{
    pthread_t t[3];
    int id[3] = {1, 2, 3};
    
    pthread_mutex_init(&lock, NULL); // Create the lock (make the key)
    
    for (int i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, work, &id[i]);
    
    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);
    
    pthread_mutex_destroy(&lock);    // Clean up the lock
    printf("Final counter = %d\n", counter);
    return 0;
}