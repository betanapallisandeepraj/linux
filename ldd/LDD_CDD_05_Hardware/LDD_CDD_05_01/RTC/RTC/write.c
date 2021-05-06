/* This program shows how to access clock using our driver
*/

# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
main(){
	int fd,i;
	unsigned char data;
	fd = open("/dev/clock",O_RDWR,0777);
	if(fd < 0){
		perror("clock:");
		exit(1);
	}
	data =0x04;
	for(i=0;i<6;i++){
		write(fd,&data,1);
		printf(" .... %x....\n",data);
	}
}			
