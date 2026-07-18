#include <stdio.h>
#include <pthread.h>

int balance = 0;
pthread_mutex_t lock1, lock2;          // Two locks - like two keys for two rooms

// Race condition: show what goes wrong without lock
void *unsafe_work(void *arg) 
{
    int id = *(int *)arg;
    for (int i = 0; i < 100000; i++)
        balance++;                      // Without lock - threads crash into each other
    return NULL;
}

// Deadlock prevention: use trylock (ask for key, if busy move on)
void *safe_work(void *arg) 
{
    int id = *(int *)arg;
    
    // trylock = ask for key, if not available don't wait (prevents deadlock)
    while (1) 
    {
        if (pthread_mutex_trylock(&lock1) == 0)       // Got key1?
        {
            if (pthread_mutex_trylock(&lock2) == 0)   // Got key2?
            {
                balance++;                             // Do work safely
                pthread_mutex_unlock(&lock2);          // Return key2
                pthread_mutex_unlock(&lock1);          // Return key1
                break;                                 // Done, exit loop
            }
            pthread_mutex_unlock(&lock1);              // Return key1, try again
        }
    }
    return NULL;
}

int main() 
{
    pthread_t t[2];
    int id[2] = {1, 2};
    
    // --- Demo 1: Race condition (wrong result) ---
    printf("--- Race Condition Demo ---\n");
    balance = 0;
    for (int i = 0; i < 2; i++)
        pthread_create(&t[i], NULL, unsafe_work, &id[i]);
    for (int i = 0; i < 2; i++)
        pthread_join(t[i], NULL);
    printf("Expected: 200000, Got: %d (wrong!)\n\n", balance);
    
    // --- Demo 2: Deadlock prevention (correct result) ---
    printf("--- Deadlock Prevention Demo ---\n");
    balance = 0;
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);
    
    for (int i = 0; i < 2; i++)
        pthread_create(&t[i], NULL, safe_work, &id[i]);
    for (int i = 0; i < 2; i++)
        pthread_join(t[i], NULL);
    
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    printf("Expected: 2, Got: %d (correct!)\n", balance);
    
    return 0;
}   