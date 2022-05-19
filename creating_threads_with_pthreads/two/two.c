#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

long sum = 0;

void* threadBody (void* thread_data){
	for (long i = 0; i < 1000000 ; i++) sum++;

	pthread_exit(0);
}

int main(int argc, char* argv[]){
	void* thread_data = NULL;
	int number_threads = atoi(argv[1]);
	pthread_t threads[number_threads];

	for (int i = 0; i < number_threads; i++) pthread_create(&threads[i], NULL, threadBody, thread_data);

	for (int i = 0; i < number_threads; i++) pthread_join(threads[i], NULL);

	printf("Sum after %d threads is %ld\n", number_threads, sum);

	pthread_exit(0);
	return 0;
}
