#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct stat buf;
    stat("/etc/hosts", &buf);
    printf("/etc/hosts file size = %d\n", (int)buf.st_size);
    printf("/etc/hosts file dev - %d\n",(int)buf.st_dev);
}