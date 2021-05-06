#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <linux/process.h>

struct add {
	int a;
	int b;
};
struct add addtest;

int main()
{	
	int fd, result;
	//char  ubuff[80]="hai hello world", kbuff[80];
	addtest.a = 35;
	addtest.b = 5;
	fd = open ("/dev/MyCharDevice0", O_RDWR , 0777 ) ;
	if (fd <0 )
	{	
		perror ("open:%s") ;
		exit (-1 ) ;
	}
	if(write ( fd, &addtest, sizeof ( struct add ) ) < 0)
		perror("write") ;
	sleep(2);
	if(read ( fd, &result, 4 ) < 0)
		perror("read") ;
	printf ("\n Kernel Data: %d", result);
	close(fd);
	return 0 ;
}


