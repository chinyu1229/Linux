#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#define BUF_SIZE 1024
void failure(const char *fcall)
{
	perror(fcall);
	exit(EXIT_FAILURE);
}
int main(int argc,char *const argv[])
{
	int opt;
	int is_append = 0;
	int fd,flags;
	int fds[128];
	mode_t mode;
	char buf[BUF_SIZE];
	ssize_t numRead;
	int i, numFiles = 0;

	while((opt = getopt(argc,argv,"a::")) != -1)
	{
		switch(opt){
			case 'a':
				is_append = 1;
				printf("have-%c\n",'a');
				break;
			case '?':
				fprintf(stderr,"Usage:%s [-a] <file1> <file2>...<fileN>\n",argv[0]);
				exit(EXIT_FAILURE);
				break;
		}
	}

	flags = O_CREAT | O_WRONLY;
	mode = S_IRUSR | S_IWUSR; // rw //
	if(is_append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	
	for(i = optind;i < argc ;i++)
	{
		fds[i - optind] = fd = open(argv[i],flags,mode);
		if(fd == -1)
			failure("open");
		++numFiles;
	}
	while((numRead = read(STDIN_FILENO,buf, sizeof(buf) )) > 0)
	{
		if(write(STDOUT_FILENO,buf,numRead) != numRead) failure("write");

		for(i = 0;i < numFiles; i++)
		{
			if(write(fds[i],buf,numRead)!=numRead)
				failure("write");
		}
	}
	if(numRead == -1) failure("read");

	for(i = 0;i < numFiles; i++)
	{
		if(close(fds[i] == -1)) failure("close");
	}
	return 0;
}
			



