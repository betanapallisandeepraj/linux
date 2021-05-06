#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>


int id;
int count;

irqreturn_t handler(int irq, void *id)
{

	printk("inside the handler\n");
        count++;
        printk("The count is %d \n",count);
        return 0;
}

int init_module(void)
{
	int rv;
	printk("simple modules loaded\n");
	rv = request_irq(23, handler, IRQF_SHARED, "sandeepraj_irq", &id); 	
        if (rv )
        {
                printk ("<1>can't get interrupt 1\n");
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

