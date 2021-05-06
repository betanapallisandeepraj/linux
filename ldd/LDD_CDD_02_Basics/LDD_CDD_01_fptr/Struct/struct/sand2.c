#include<stdio.h>
#include "sand.h"

int sand2_open(int );
int sand2_read(int );


struct file_ops sand2_ops = {
	.open = sand2_open,
	.read = sand2_read,
};

int sand2_open(int x)
{
	printf ("This is sand2_open x:%d\n",x);
	return 0;	
}


int sand2_read(int x)
{
	printf ("This is sand2_read x:%d\n",x);
	return 0;	
}

fun_sand2 ()
{
	struct file_ops *fptr;
	fptr = &sand2_ops;
        fptr->open(3); 	
        fptr->read(4); 

}


