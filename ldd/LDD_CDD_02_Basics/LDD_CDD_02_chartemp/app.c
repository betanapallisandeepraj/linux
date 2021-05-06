
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fd, count;
        char buff="12345";
	fd = open("/dev/MyChar", O_RDWR);
	printf("fd:%d\n", fd);
       
        count = write(fd,buff,2);
	printf("count:%d\n", count);
        
	count = read(fd,buff,2);
	printf("count:%d\n", count);
         
}
