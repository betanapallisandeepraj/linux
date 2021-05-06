/* hello_param.c */
#include <linux/init.h> // __init and __exit
#include <linux/module.h> // MODULE_LICENSE(), module_init......
#include <linux/moduleparam.h> // module_param()

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sandeep Raj");

/* A couple of parameters that can be passed in: how many times we say
   hello, and to whom */

static char *whom = "world";
module_param(whom, charp, 0);
static int howmany = 1;
module_param(howmany, int, 0);

static int __init hello_init(void)
{
    int i;
    for (i = 0; i < howmany; i++)
    	printk(KERN_ALERT "(%d) Hello, %s\n", i, whom);
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, %s\n", whom);
}

module_init(hello_init);
module_exit(hello_exit);