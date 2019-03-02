#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
/*
struct stat {
    dev_t         st_dev;       //文件的设备编号
    ino_t         st_ino;       //节点
    mode_t        st_mode;      //文件的类型和存取的权限
    nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1
    uid_t         st_uid;       //用户ID
    gid_t         st_gid;       //组ID
    dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号
    off_t         st_size;      //文件字节数(文件大小)
    unsigned long st_blksize;   //块大小(文件系统的I/O 缓冲区大小)
    unsigned long st_blocks;    //块数
    time_t        st_atime;     //最后一次访问时间
    time_t        st_mtime;     //最后一次修改时间
    time_t        st_ctime;     //最后一次改变时间(指属性)
};
*/
int main(int argc,char* argv[])
{
    if(argc !=2){
        printf("./ls_ls filename\n");
        return -1;
    }
    //调用stat，得到文件属性信息
    struct stat sb;
    stat(argv[1],&sb);

    //解析属性信息,st_mode,
    char stmode[11] = {0};
    if(S_ISREG(sb.st_mode))
        stmode[0]= '-';
    if(S_ISDIR(sb.st_mode))
        stmode[0] = 'd';
    if(S_ISCHR(sb.st_mode))
        stmode[0] = 'c';
    if(S_ISBLK(sb.st_mode))
        stmode[0] = 'b';
    if(S_ISFIFO(sb.st_mode))
        stmode[0] = 'p';
    if(S_ISLNK(sb.st_mode))
        stmode[0] = 'l';
    if(S_ISSOCK(sb.st_mode))
        stmode[0] = 's';

    //解析权限
    /*
    S_IFMT   0170000    文件类型的位遮罩
    S_IFSOCK 0140000    scoket
    S_IFLNK 0120000     符号连接
    S_IFREG 0100000     一般文件
    S_IFBLK 0060000     区块装置
    S_IFDIR 0040000     目录
    S_IFCHR 0020000     字符装置
    S_IFIFO 0010000     先进先出

    S_ISUID 04000     文件的(set user-id on execution)位
    S_ISGID 02000     文件的(set group-id on execution)位
    S_ISVTX 01000     文件的sticky位

    S_IRUSR(S_IREAD) 00400     文件所有者具可读取权限
    S_IWUSR(S_IWRITE)00200     文件所有者具可写入权限
    S_IXUSR(S_IEXEC) 00100     文件所有者具可执行权限

    S_IRGRP 00040             用户组具可读取权限
    S_IWGRP 00020             用户组具可写入权限
    S_IXGRP 00010             用户组具可执行权限

    S_IROTH 00004             其他用户具可读取权限
    S_IWOTH 00002             其他用户具可写入权限
    S_IXOTH 00001             其他用户具可执行权限
    */
    if(sb.st_mode & S_IRUSR) stmode[1]= 'r';
    else stmode[1] = '-';
    if(sb.st_mode & S_IWUSR) stmode[2]= 'w';
    else stmode[2] = '-';
    if(sb.st_mode & S_IXUSR) stmode[3]= 'x';
    else stmode[3] = '-';
    if(sb.st_mode & S_IRGRP) stmode[4]= 'r';
    else stmode[4] = '-';
    if(sb.st_mode & S_IWGRP) stmode[5]= 'w';
    else stmode[5] = '-';
    if(sb.st_mode & S_IXGRP) stmode[6]= 'x';
    else stmode[6] = '-';
    if(sb.st_mode & S_IROTH) stmode[7]= 'r';
    else stmode[7] = '-';
    if(sb.st_mode & S_IWOTH) stmode[8]= 'w';
    else stmode[8] = '-';
    if(sb.st_mode & S_IXOTH) stmode[9]= 'x';
    else stmode[9] = '-';
    //时间获取
    struct tm *filetm = localtime(&sb.st_mtime);
    char timebuf[20] = {0};
    sprintf(timebuf,"%d月  %d %02d:%02d",filetm->tm_mon+1,filetm->tm_mday,filetm->tm_hour,filetm->tm_min);

    printf("%s %ld %s %s %ld %s %s\n",stmode,sb.st_nlink,getpwuid(sb.st_uid)->pw_name,getgrgid(sb.st_gid)->gr_name,sb.st_size,timebuf,argv[1]);
    return 0;
}