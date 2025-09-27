//g++ singlepthreadhello.c -o singlepthreadhello -pthread
//./singlepthreadhello
#include <cstdio>
#include<pthread.h>


void* threadfunction(void*arg){

printf("Hello\n");	

pthread_exit(NULL);

}



int main() {


pthread_t tid;

int result = pthread_create (&tid,NULL,threadfunction,NULL);

pthread_join(tid, NULL);

	
	

//	threadfunction();
    return 0;
}

