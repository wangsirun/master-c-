#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int fd, offset;
    struct stat sbuf;
    printf("offet is %s", argv[1]);

    if (argc != 2)
    {
        fprintf(stderr, "usage:readfile offset\n");
        exit(1);
    }

    if ((fd = open("readfile.cpp", O_RDONLY)) == -1)
    { //打开文件自身
        perror("open");
        exit(1);
    }

    if (stat("readfile.cpp", &sbuf) == -1)
    { //文件大小，mmap的有效内存大小不超过该值
        perror("stat");
        exit(1);
    }

    offset = atoi(argv[1]); //文件偏移量
    if (offset < 0 || offset > sbuf.st_size - 1)
    {
        fprintf(stderr, "readfile: offset must be in the range 0-%ld\n",
                sbuf.st_size - 1);
        exit(1);
    }

    void *data = mmap((caddr_t)0, sbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);

    if (data == (caddr_t)(-1))
    {
        perror("mmap");
        exit(1);
    }
    char *datas = static_cast<char *>(data);

    printf("byte at offset %d is '%c'\n", offset, datas[offset]);

    return 0;
}