#include <iostream>
#include <pthread.h>

// Global variable shared by the threads
long long counter = 0;

// Function for the threads to run
void* increment_counter(void* arg) {
    for (int i = 0; i < 100000; ++i) {
        // This is a "read-modify-write" operation, which is not atomic.
        // It can be interrupted by another thread, causing a race condition.
        counter++; 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final result
    // The expected output is 200000, but it will be less because of the race condition.
    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
