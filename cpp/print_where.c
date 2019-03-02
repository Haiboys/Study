#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	close(1);
	int fd = open("1.log",O_CREAT|O_TRUNC|O_WRONLY,0644);
	printf("hello world!\n");
	fflush(stdout);
	close(fd);
	return 0;
}
