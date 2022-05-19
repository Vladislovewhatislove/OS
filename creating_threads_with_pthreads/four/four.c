#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

long sum = 0;
pthread_mutex_t sumlock;

void* threadBody (void* thread_data){
	printf("Hello, I'm process №%d\n", syscall(SYS_gettid));

	long temp = 0;

	for (long i = 0; i < 1000000 ; i++) temp++;
	pthread_mutex_lock(&sumlock);
	sum += temp;
	pthread_mutex_unlock(&sumlock);

	pthread_exit(0);
}

int main(int argc, char* argv[]){
	void* thread_data = NULL;
	int number_threads = atoi(argv[1]);
	pthread_t threads[number_threads];
	pthread_mutex_init(&sumlock, NULL);

	for (int i = 0; i < number_threads; i++){
		pthread_create(&threads[i], NULL, threadBody, thread_data);	
	}

	for (int i = 0; i < number_threads; i++){
		pthread_join(threads[i], NULL);
	}

	printf("Sum after %d threads is %ld\n", number_threads, sum);

	pthread_mutex_destroy(&sumlock);
	pthread_exit(0);
	return 0;
}
