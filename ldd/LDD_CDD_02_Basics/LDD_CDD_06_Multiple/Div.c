#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct div {
	int a;
	int b;
};
struct div divtest;

int main()
{	
	int fd, result;
	//char  ubuff[80]="hai hello world", kbuff[80];
	divtest.a = 35;
	divtest.b = 5;
	fd = open ("/dev/div", O_RDWR , 0777 ) ;
	if (fd <0 )
	{	
		perror ("open:%s") ;
		exit (-1 ) ;
	}
	if(write ( fd, &divtest, sizeof ( struct div ) ) < 0)
		perror("write") ;
	sleep (4);
	if(read ( fd, &result, 4 ) < 0)
		perror("read") ;
	printf ("\n Kernel Data: %d", result);
	close(fd);
	return 0 ;
}


