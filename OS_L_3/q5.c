#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int main()
{
	// Declare x and assign it a value
	int x;
	x = 100;
	printf("Current value of x: %d\n", x); 
	
	// fork the parent process
	int temp_pid = fork();
	
	// if fork failed, return
	if (temp_pid < 0)
	{
		printf("%s", "Fork statement failed\n");
		return 0;
	}
	
	// if child, then
	else if (temp_pid > 0)
	{
		printf("Current value(Inside Child process): %d\n", x);
		x = x + 7;
		printf("New value after adding 7: %d\n", x);
	}
	
	// if parent, then
	else
	{
		int temp = wait(NULL);
		printf("Current value(Inside Parent process): %d\n", x);
		x = x - 7;
		printf("New value after substracting 7: %d\n", x);
	}
}
