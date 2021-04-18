#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int fd = open("file",O_RDWR|O_CREAT|O_APPEND);
	if(fd < -1)
	{
		perror("open");
		exit(-1);
	}
	lseek(fd,0,SEEK_SET);

	write(fd, argv[1],strlen(argv[1]));
	close(fd);

	return 0;
}
