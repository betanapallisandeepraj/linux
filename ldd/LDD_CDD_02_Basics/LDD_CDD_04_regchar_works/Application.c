
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
int main()
{
	int FileDesc;
	char Ubuff[]="THis is the User Buffer......Sending Data to the Kernel....";
	char Kbuff[100];	
	FileDesc=open("/dev/mychar",O_RDWR,0777);
	if(FileDesc <0)
	{
		printf("\nError Opening Device\n");	
		exit(1);
	}
	write(FileDesc,Ubuff,sizeof(Ubuff));
	read(FileDesc,Kbuff,sizeof(Ubuff));
	printf("\n The Data read from the Kernel is\n>>>> %s <<<<\n",Kbuff);
	close(FileDesc);
}
