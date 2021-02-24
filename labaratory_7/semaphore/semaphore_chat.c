#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;

struct memory { 
	char buff[100]; 
}; 

struct memory* shmptr; 

void initialDataFromUser1() {
	printf("User1 init: ");
	fgets(shmptr->buff, 100, stdin);
}

// handler function to print message received from user2

void* handler1() 
{
	sem_wait(&mutex);
	printf("\nReceived From User2: %s", shmptr->buff); 

	printf("User1: ");
	fgets(shmptr->buff, 100, stdin); 

	sem_post(&mutex);
} 

// handler function to print mesage received from user1

void* handler2() 
{ 
	sem_wait(&mutex);

	printf("\nReceived From User1: %s", shmptr->buff); 
	
	printf("User2: ");
	fgets(shmptr->buff, 100, stdin); 

	sem_post(&mutex);
} 

// main function 
int main() 
{ 
	// key value of shared memory 
	int key = 12345; 
	
	// shared memory create 
	int shmid = shmget(key, sizeof(struct memory), IPC_CREAT | 0666); 

	// attaching the shared memory 
	shmptr = (struct memory*)shmat(shmid, NULL, 0);

	// semaphore
	sem_init(&mutex, 0, 1);

	initialDataFromUser1();

	pthread_t user1, user2;

	while (1) { 
		pthread_create(&user1, NULL, handler1, NULL);
		pthread_create(&user2, NULL, handler2, NULL);
	
		pthread_join(user2, NULL);	
		pthread_join(user1, NULL);
	} 

	sem_destroy(&mutex);

	shmdt((void*)shmptr); 

	return 0; 

} 