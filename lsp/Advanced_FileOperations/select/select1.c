#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	fd_set read_fileset,testfd;
	int fd2,fd3, retfd;
	int buf;
	int val,ret;
	char buff[4099];
	fd2=open("/dev/input/event1",O_RDONLY);
	if(fd2<0)
		printf("error while open the file event1\n");
	fd3=open("/dev/input/event3",O_RDONLY);
	if(fd3<0)
		printf("error while open the file event2\n");
	
	//while(1) {
	/* initially makes as zero files */
	FD_ZERO(&read_fileset);

	/* add our file discriptors */
	FD_SET(fd2,&read_fileset);
	FD_SET(fd3,&read_fileset);

while(1){
	testfd=read_fileset;
	retfd=select(FD_SETSIZE,&testfd,NULL,NULL,0);
	printf ("retfd:%d\n",retfd);
	if(retfd<0){
		printf("select is failed\n");
		return -1;
		}
	/* Touch screen data event0  */
	if(FD_ISSET(fd2,&testfd))
		{
		printf("data is available on  power button event1\n");
		ret = read(fd2,&buff,4010);
		printf ("ret:%d\n",ret);
		}
	if(FD_ISSET(fd3,&testfd))
		{
		printf("data is available on mouse event2\n");
		ret = read(fd3,&buff,4096);
		printf ("ret:%d\n",ret);
		}
	}
	return 0;
}
		
