#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
	FILE * fp = fopen(argv[1], "r");
	
	if (fp == NULL) {
		printf("Failed to open the file with name: %s\n", argv[1]);
		return 1;
	
	}
	
	unsigned int startTime = clock();
	
	int characterCounter = 0;
	
	do {
		char c = fgetc(fp);
		
		characterCounter++;
		
		printf("%c", c);
	} while (!feof(fp));
	
	unsigned int endTime = clock();
	unsigned int workTime = endTime - startTime;
	
	printf("\n\n+++++++++++++++++++++++++++++++++++\n");
	printf("\nNumber f characters in file \"%s\" is equel %d\n", argv[1], characterCounter);
	printf("Work time with parallel counting is equel %d\n", workTime);
	printf("\n+++++++++++++++++++++++++++++++++++\n");
	
	if (fclose(fp) != 0) {
		printf("Failed to close the file\n");
		return 1;
	}
	
	return 0;
}