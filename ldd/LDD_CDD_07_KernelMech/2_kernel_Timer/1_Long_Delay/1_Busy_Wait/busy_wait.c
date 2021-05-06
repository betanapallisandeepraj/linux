#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

static __init int myinit(void)
{
	unsigned long j = jiffies + 10*HZ;
	printk("Try to do something for the next 10 seconds.\n");
	printk("I am putting the system off to a standstill for the\n"
	       "next 10 seconds");
	while( jiffies < j ) { 
		
                }
	printk("Now I am out of the loop");
	return -1; /* dont load the module */
}

static __exit void myexit(void)
{
printk("\nModule Successfully removed");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sandeep Raj");
MODULE_DESCRIPTION ("Example: Kernel Long Delays");

module_init(myinit);
module_exit(myexit);



