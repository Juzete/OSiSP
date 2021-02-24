// C program to demonstrate use of fork() and pipe() 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    // We use two pipes  
  
    int fd1[2];  // Used to store two ends of first pipe 
    int fd2[2];  // Used to store two ends of second pipe 
  
    char output_str[80]; 
    char input_str[80]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    {
		while (1) {
			// Take an input arr2ing from user.
			// 80 is maximum length			
			printf("First user should write any message: ");
			fgets(input_str, 80, stdin);

			// Write the input string
			write(fd1[1], input_str, strlen(input_str) + 1);
			
			// Waiting an answer from second user
			// wait(NULL);
			
			// Read message from second user
			read(fd2[0], output_str, 80);
			
			// Print the read message
			printf("Second user wrote: %s\n", output_str);
		}
    } 
  
    // child process 
    else
    { 
		while (1) {
			// Read the message
			read(fd1[0], output_str, 80);
			
			// Print the read message
			printf("First user wrote: %s\n", ouput_str);
	
			// Take an input from user
			printf("Second user should write any message");
			fgets(input_str, 80, stdin);

			// Write the input string	
			write(fd2[1], input_str, strlen(input_str) + 1);
		}
    } 
} 