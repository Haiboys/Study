#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char* argv[])
{
    if(argc != 2){
        printf("./filesize filename\n");
        return -1;
    }
    int fd = open(argv[1],O_RDONLY);
    int ret = lseek(fd,0,SEEK_END);
    printf("file size is:%d\n",ret);
    close(fd);
    return 0;
}