#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
	int fd,c=0;
	char a='H',b='\0';
	if(argc<2) {
		printf("Please give serial device as 2nd argument\n");
		return 0;
	}
	fd=open(argv[1],O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd<0) {
		printf("Could not open usb device\n");
		return 0;
	}
	printf("serial device entered as %s\n",argv[1]);
	while(1) {
		write(fd,&a,1);
		read(fd,&b,1);
		write(1,&b,1);
		b='\0';
	}
	return 0;
}
