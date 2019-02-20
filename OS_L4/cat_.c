#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

void main(int argc, char *argv[])
{
	// Proceed for one-one file
	for (int i = 1; i < argc; i++)
	{
		// Add new file descriptor
		int fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			perror("Could not open file.");
			return;
		}
		
		// Initialize buffer
		char *c = (char *) malloc(sizeof(1));
		
		// Read and write one-one character
		int a = read(fd, c, 1);
		while(a > 0)
		{
			//printf("%c", *c);
			write(1, c, 1);
			a = read(fd, c, 1);
		}
		
		// Remove file descriptor
		close(fd);
	}
}
