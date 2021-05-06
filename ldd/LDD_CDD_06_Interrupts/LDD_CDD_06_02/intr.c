#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>


struct tasklet_struct task;
int id;
int count;

void my_func(unsigned long);
void my_func(unsigned long data)
{
	printk("tasklet is scheduled\n");
}

irqreturn_t handler(int irq, void *id)
{

      printk("inside the handler\n");
       count++;
       printk("ISR calling %d \n",count);
        tasklet_schedule(&task);
        printk("Tasklet calling %d \n",count);
	return IRQ_HANDLED;
}

int init_module(void)
{
	int rv;
	task.func=&my_func;
	
	printk("simple modules loaded\n");
 	rv = request_irq(23, handler, IRQF_SHARED , "sandeepraj_irq", &id); 
	if (rv )
	{
	 	printk ("<1>can't get interrupt 12\n");
	return -1;
	}
	return 0;
}

void cleanup_module(void)
{
	printk("simple module unloaded\n");
	free_irq(23, &id);   
}
MODULE_AUTHOR ("Sandeep Raj");
MODULE_DESCRIPTION ("Android for Embedded Systems");
MODULE_LICENSE("GPL");

