#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 
  
int main() 
{ 
    // ftok to generate unique key 
    key_t stateKey = ftok("state",65);
	if (stateKey == -1) {
		perror("ftok");
		exit(1);
	}
	key_t messageKey = ftok("message", 66);
		if (messageKey == -1) {
		perror("ftok");
		exit(1);
	}
	
    // shmget returns an identifier in shmid 
    int shmMessageID = shmget(messageKey,1024,0666|IPC_CREAT);
	int shmStateID = shmget(stateKey,1024,0666|IPC_CREAT);
  
	pid_t idFork = fork();
	if (idFork < 0) {
		// error
	} else if (idFork == 0) {
		// child process
		
		// atach to shared memory
		int * state = (int*) shmat(shmStateID,(void*)0,0);
		char * message = (char*) shmat(shmMessageID,(void*)0,0);
		
		*state = 1;
		
		while (1) {
			
			// waiting
			while (*state == 1) {
				// do nothing
			}
			
			// printing first user's message 
			printf("First user writes: %s\n", message);
			
			// getting data from second user
			printf("Second user: ");
			fgets(message,80,stdin);
			
			// changing the program state
			*state = 1;
		}
		
		// detach from shared memory
		shmdt(state);
		shmdt(message);
	} else {
		// parent process
		
		// atach to shared memory
		int * state = (int*) shmat(shmStateID,(void*)0,0);
		char * message = (char*) shmat(shmMessageID,(void*)0,0);
		
		*state = 1;
		
		while (1) {

			// getting data from first user
			printf("First user: ");
			fgets(message,80,stdin);
			
			// changing the program state
			*state = 0;
			
			// waiting
			while(*state == 0) {
				// do nothing
			}
			
			// printing second user's message 
			printf("Second user writes: %s\n", message);
			
		}
		
		// detach from shared memory
		shmdt(state);
		shmdt(message);
		
		// destroy the shared memory
		shmctl(shmStateID,IPC_RMID,NULL); 		
		shmctl(shmMessageID,IPC_RMID,NULL); 
	}  
}
