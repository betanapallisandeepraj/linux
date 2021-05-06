#include<stdio.h>
#include "sand.h"

int sand1_open(int );
int sand1_read(int );

struct file_ops sand1_ops = {
	.open = sand1_open,
	.read = sand1_read,
};

int sand1_open(int x)
{
	printf ("This is sand1_open x:%d\n",x);
	return 0;	
}


int sand1_read(int x)
{
	printf ("This is sand1_read x:%d\n",x);
	return 0;	
}

main ()
{
	struct file_ops *fptr;
	fptr = &sand1_ops;
        fptr->open(1); 	
        fptr->read(2); 
	
	fun_sand2();

}

