#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void getEndedProcessInfo(pid_t cpid, pid_t ppid) {
	printf("Child process with pid %d is ended and process with pid %d continues its implementation\n", cpid, ppid);
}

int main() {
	printf("Hello, I start this program and my pid is %d\n", getpid());

	if (fork() == 0) {
		printf("Hello, I'm pid2 = %d\n", getpid());
		exit(0);
	}
	getEndedProcessInfo(wait(NULL), getpid());
 
	if (fork() == 0) {
		printf("Hello, I'm pid3 = %d\n", getpid());
   
   		if (fork() == 0) {
     			printf("Hello, I'm pid5 = %d\n", getpid());

			if (fork() == 0) {
                        	printf("Hello, I'm pid7 = %d\n", getpid());
                        	exit(0);
                	}
                	getEndedProcessInfo(wait(NULL), getpid());

     			exit(0);
   		}

		getEndedProcessInfo(wait(NULL), getpid());

		if (fork() == 0) {
			printf("Hello, I'm pid6 = %d\n", getpid());
			
			char *binaryPath = "/bin/ls";
			char *arg1 = "-lh";
			char *arg2 = "/home/krutilins";
			execl(binaryPath,arg1, arg2, NULL);
		}
  		getEndedProcessInfo(wait(NULL), getpid());

		exit(0);
	}
	getEndedProcessInfo(wait(NULL), getpid());

	if (fork() == 0) {
		printf("Hello, I'm pid4 = %d\n", getpid());
		exit(0);
	}
	getEndedProcessInfo(wait(NULL), getpid());
	
	printf("This program is ended");

	return 0;
}