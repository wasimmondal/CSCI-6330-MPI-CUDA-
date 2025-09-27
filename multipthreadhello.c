//g++ singlepthreadhello.c -o singlepthreadhello -pthread
//./singlepthreadhello
#include <cstdio>
#include<pthread.h>


const int NUM_THREADS=4; 




void* threadfunction(void*arg){

int thread_id = *(int*)arg;

printf("Hello from thread %d\n", thread_id);
pthread_exit(NULL);

}



int main() {


pthread_t tid[NUM_THREADS];
int ids[NUM_THREADS];


for (int i=0; i<NUM_THREADS; i++)
{	
ids[i]=i;

//int result = 

pthread_create (&tid[i],NULL,threadfunction,&ids[i]);

/*
if (result != 0) {
            printf("Error creating thread %d, code: %d\n", i, result);
            return 1;
        }

*/

  // Wait for all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }



}	
	

//	threadfunction();
    return 0;
}

