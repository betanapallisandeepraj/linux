#include <stdio.h>
#include "hello.h" 

int sand2_open (int x);
int sand2_read (int z);
void fun_sand2(void);

struct  hello sand2 = {
 	"sand_Driver",
	.open = sand2_open,
	.read = sand2_read,
};

int sand2_open (int x)
{
	printf("sand2_open:%d\n",x);
}

int sand2_read (int z)
{
	printf("sand2_read:%d\n",z);
}

void fun_sand2 ()
{
struct hello *fops2 = &sand2;
fops2->open(9);
fops2->read(10);

}





