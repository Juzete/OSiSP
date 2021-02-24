#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;

void* counting(void* fileName) {
	FILE * fp = fopen((char*)fileName, "r");
	
	if (fp == NULL) {
		printf("Failed to open the file with name: %s\n", (char*)fileName);
		return NULL;
	}
	
	int characterCounter = 0;
	
	do {
		fgetc(fp);
		characterCounter++;
	} while(!feof(fp));
	
	if (fclose(fp) != 0) {
		printf("Failed to close the file\n");
		return NULL;
	}
	
	sem_wait(&semaphore);
	
	printf("\n================================================================\n");
	printf("\nNumber f characters in file \"%s\" is equel %d\n", (char*)fileName, characterCounter);
	printf("\n================================================================\n");
	
	sem_post(&semaphore);
	
	return characterCounter;
}

void* printing(void* fileName) {
	FILE * fp = fopen((char*)fileName, "r");
	
	if (fp == NULL) {
		printf("Failed to open the file with name: %s\n", (char*)fileName);
		return NULL;
	}
	
	sem_wait(&semaphore);
	
	do {
		printf("%c", fgetc(fp));
	} while (!feof(fp));
	
	sem_post(&semaphore);
	
	if (fclose(fp) != 0) {
		printf("Failed to close the file\n");
		return NULL;
	}
}

int main(int argc, char* argv[]) {
	sem_init(&semaphore, 0, 1);
	
	pthread_t printingThread;
	pthread_t countingThread;
	
	int characterCounter;
	
	unsigned int startTime = clock();
	
	pthread_create(&printingThread, NULL, printing, (void*)argv[1]);
	pthread_create(&countingThread, NULL, counting, (void*)argv[1]);

	pthread_join(printingThread, NULL);
	pthread_join(countingThread, (void**)&characterCounter);
	
	unsigned int endTime = clock();
	unsigned int workTime = endTime - startTime;
	
	printf("\n\n+++++++++++++++++++++++++++++++++++\n");
	printf("\nNumber f characters in file \"%s\" is equel %d\n", argv[1], characterCounter);
	printf("Work time with separate counting is equel %d\n", workTime);
	printf("\n+++++++++++++++++++++++++++++++++++\n");
	
	return 0;
}