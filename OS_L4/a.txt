#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

void main(int argc, char *argv[3])
{
	int fd = open(argv[1], O_RDONLY);
	int fd_1 = open(argv[2], O_WRONLY | O_CREAT);
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
	
	char *c = (char *) malloc(sizeof(1));
	int a = read(fd, c, 1);
	while(a > 0)
	{
		write(fd_1, c, 1);
		a = read(fd, c, 1);
	}
	close(fd);
}
