#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_body (void* thread_data){
	for (int i = 0; i < 10; i++) printf("Hello, I'm process №%d\n", syscall(SYS_gettid));
	
	pthread_exit(0);
}

int main(int argc, char* argv[]){
	void* thread_data = NULL;
	int number_threads = atoi(argv[1]);
	pthread_t thread[number_threads];

	for (int i = 0; i < number_threads; i++) pthread_create(&thread[i], NULL, thread_body, thread_data);

	for (int i = 0; i < number_threads; i++) pthread_join(thread[i], NULL);
	
	pthread_exit(0);
	return 0;
}
