#include <stdio.h>
#include "hello.h" 

int sand1_open (int x);
int sand1_read (int z);
void fun_sand2(void);
struct  hello sand1 = {
 	"sand_Driver",
	.open = sand1_open,
	.read = sand1_read,
};

int sand1_open (int x)
{
	printf("sand1_open:%d\n",x);
}

int sand1_read (int z)
{
	printf("sand1_read:%d\n",z);
}

main ()
{
struct hello *fops1 = &sand1;
fops1->open(5);
fops1->read(8);
fun_sand2();
}





