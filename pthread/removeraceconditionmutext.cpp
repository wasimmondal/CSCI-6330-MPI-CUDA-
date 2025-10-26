#include <iostream>
#include <pthread.h>

// Global variable and mutex
long long counter = 0;
pthread_mutex_t mutex_lock; // Declares the mutex

// Function for the threads to run, now with mutex protection
void* increment_counter_safe(void* arg) {
    for (int i = 0; i < 100000; ++i) {
        // Lock the mutex before accessing the shared resource
        pthread_mutex_lock(&mutex_lock);

        // This critical section is now protected.
        // Only one thread can be here at a time.
        counter++;

        // Unlock the mutex after the operation is complete
        pthread_mutex_unlock(&mutex_lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex before use
    pthread_mutex_init(&mutex_lock, NULL);

    // Create two threads
    pthread_create(&thread1, NULL, increment_counter_safe, NULL);
    pthread_create(&thread2, NULL, increment_counter_safe, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex_lock);

    // Print the final result
    // The output will reliably be 200000.
    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
