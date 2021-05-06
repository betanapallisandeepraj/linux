/* This program shows how to access clock using our drive
*/
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
main(){
	int fd,i;
	unsigned char data;
	fd = open("/dev/clock",O_RDONLY);
	if(fd < 0){
		perror("clock:");
	exit(1);
	}
	//data =0x04;
	for(i=0;i<6;i++){
		read(fd,&data,1);
		printf(" .... %x....\n",data);
//		perror("aa");
	}
}			
 
