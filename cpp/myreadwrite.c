#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc,char* argv[])
{
    if(argc != 2){
        printf("./myreadwrite filename\n");
        return -1;
    }
    int fd = open(argv[1],O_RDONLY);
    //write(fd,"helloworld",11);
    
    char buf[256] = {0};
    
    int ret = read(fd,buf,sizeof(buf));

    while(1){
        lseek(fd,0,SEEK_SET);
        write(STDOUT_FILENO,buf,ret);
        ret = read(fd,buf,sizeof(buf));
    }
    close(fd);
    return 0;
}