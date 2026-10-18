#include<stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(void){
    int fd=open("/etc/os-release",O_RDONLY);
    if (fd==-1){
        perror("open failed");
        return 1;
    };
    char buffer[256];
    while(1){
        ssize_t n=read(fd,buffer,sizeof(buffer));
    if (n==-1){
        perror("read fd error");
        close(fd);
        return 1;
    };
    if (n==0){
        break;
    }
        size_t off_set=0;
        while(off_set<(size_t)n){
            ssize_t written=write(STDOUT_FILENO,buffer+off_set,(size_t)n-off_set);
            if (written==-1){
                perror("write error");
                close(fd);
                return 1;
                };
            if (written==0){
                fprintf(stderr, "write returned 0\n");
                close(fd);
                return 1;
            };
            off_set+=(size_t)written;
        };
    }
    close(fd);
    return 0;
}