#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

void main(int argc, char *argv[2])
{
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Could not open file.");
		return;
	}
	char *c = (char *) malloc(sizeof(1));
	int a = read(fd, c, 1);
	while(a > 0)
	{
		//printf("%c", *c);
		write(1, c, 1);
		a = read(fd, c, 1);
	}
	close(fd);
}
