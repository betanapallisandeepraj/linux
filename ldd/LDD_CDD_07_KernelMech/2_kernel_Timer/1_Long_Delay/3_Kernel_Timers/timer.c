#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <asm/param.h>

#include <linux/timer.h>
struct timer_list my_timer;

static void timer_func(unsigned long func_parameter)
{
	/* Do work to be done periodically */
	printk ("inside timer_func value:%d",func_parameter );
	/* ... */
}


static int __init my_init (void)
{
	unsigned long value;
	value=10;
	printk ("init section\n");
	init_timer(&my_timer); /* Also see setup_timer() */
	my_timer.expires = jiffies + 5*HZ; /* n is the timeout in number of seconds */
	my_timer.function = timer_func; /* Function to execute after n seconds */
	my_timer.data = value; /* Parameter to be passed to timer_func */
	add_timer(&my_timer); /* Start the timer */
	return 0;
}

static void __exit my_exit (void)
{
	del_timer(&my_timer);
}

module_exit (my_exit);
module_init (my_init);

MODULE_AUTHOR("Sandeep Raj");
MODULE_DESCRIPTION("Simple demo of a kernel timer");
MODULE_LICENSE("GPL v2");
                          

