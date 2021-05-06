#include<stdio.h>

#include<linux/input.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int main()
{
	int fdev_lid,fdev_keyboard,rd,retfd;
	struct input_event ev_lid,ev_keyboard;
	fd_set read_fileset,testfd;
	fdev_lid=open("/dev/input/event2",O_RDONLY,S_IRUSR);
	fdev_keyboard=open("/dev/input/event4",O_RDONLY,S_IRUSR);
	FD_ZERO(&read_fileset);
	FD_SET(fdev_lid,&read_fileset);
        FD_SET(fdev_keyboard,&read_fileset);

	while(1)
	{
		testfd=read_fileset;
		retfd=select(FD_SETSIZE,&testfd,NULL,NULL,0);
		//printf ("retfd:%d\n",retfd);
		//printf("FD_SETSIZE: %d",FD_SETSIZE);
	        if(retfd<0)
		{
                	printf("select is failed\n");
                	return -1;
                }
		
		if(FD_ISSET(fdev_lid,&testfd))
                {
                	//printf("data is available on  lid button:\n");
			rd=read(fdev_lid,&ev_lid,sizeof(struct input_event));
			if (rd<0 ) 
			{
                	        perror("\nevtest: error reading\n");
                	        return 1;
                	}
			//printf("read lid:%d\n",rd);
	               	printf("LID Event: time %ld.%06ld, type %d , code %d , value %02x\n",
				ev_lid.time.tv_sec,ev_lid.time.tv_usec,ev_lid.type,ev_lid.code,ev_lid.value);
		}
		if(FD_ISSET(fdev_keyboard,&testfd))
                {
                       // printf("data is available on  keyboard:\n");
			rd=read(fdev_keyboard,&ev_keyboard,sizeof(struct input_event));
                        if (rd<0 )
                        {
                                perror("\nevtest: error reading\n");
                                return 1;
                        }
                       //printf("read keyboard:%d",rd);
                        printf("KEY BOARD Event: time %ld.%06ld, type %d , code %d , value %02x\n",
                                ev_keyboard.time.tv_sec,ev_keyboard.time.tv_usec,ev_keyboard.type,ev_keyboard.code,ev_keyboard.value);
                }
		FD_CLR(fdev_lid,&testfd);
		FD_CLR(fdev_keyboard,&testfd);
	}
	return 0;
}
