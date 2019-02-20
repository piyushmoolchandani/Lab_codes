#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

void main(int argc, char *argv[])
{
	if (argc != 3)
	{
		perror("Incorrect input\n");
		return;
	}
	
	// Add file descriptors
	int fd = open(argv[1], O_RDONLY);
	int fd_1 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd < 0)
	{
		perror("Could not open input file.");
		return;
	}
	if (fd_1 < 0)
	{
		perror("Could not open output file.");
		return;
	}
	
	// Initialize buffer.
	char *c = (char *) malloc(sizeof(1));
	
	// Transfer one-one character at a time.
	int a = read(fd, c, 1);
	while(a > 0)
	{
		write(fd_1, c, 1);
		a = read(fd, c, 1);
	}
	
	// Remove first file
	remove(argv[1]);
	
	// Remove file descriptors
	close(fd);
	close(fd_1);
}
