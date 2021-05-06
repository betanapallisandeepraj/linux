#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <process.h>

struct sub {
	int a;
	int b;
};
struct sub subtest;

int main()
{	
	int fd, result;
	//char  ubuff[80]="hai hello world", kbuff[80];
	subtest.a = 35;
	subtest.b = 5;
	fd = open ("/dev/MyCharDevice1", O_RDWR , 0777 ) ;
	if (fd <0 )
	{	
		perror ("open:%s") ;
		exit (-1 ) ;
	}
	if(write ( fd, &subtest, sizeof ( struct sub ) ) < 0)
		perror("write") ;
	sleep (1);
	if(read ( fd, &result, 4 ) < 0)
		perror("read") ;
	printf ("\n Kernel Data: %d", result);
	close(fd);
	return 0 ;
}


