#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>

int sand1_open (struct inode *, struct file *);
ssize_t sand1_read (struct file *, char __user *, size_t, loff_t *);
ssize_t sand1_write (struct file *, const char __user *, size_t, loff_t *);
int sand1_close (struct inode *, struct file *);

struct file_operations sand1_ops = {
	.open = sand1_open,
	.read = sand1_read,
	.write = sand1_write,
	.release = sand1_close,
}; 

int sand1_open (struct inode *fptr, struct file *fptr2)
{
	printk("This is sand1_open function\n");
	return 0;
}
ssize_t sand1_read (struct file *fptr1, char __user *fptr2, size_t len, loff_t *fptr3)
{
	printk("This is sand1_read function\n");
	return 0;
}
ssize_t sand1_write (struct file *fptr1, const char __user *fptr2, size_t len, loff_t *fptr3)
{
	printk("This is sand1_write function\n");
	return len;

}
int sand1_close (struct inode *fptr1, struct file *fptr2)
{
	printk("This is sand1_close function\n");
	return 0;
}

static int sand1_init(void) {
	int ret;
	printk ("This is sand1 init function\n");
	ret = register_chrdev(60,"sand1",&sand1_ops);
	if (ret != 0)
	return -1;

	return 0;
}


static void sand1_exit(void) {
	printk ("This is sand1 exit function\n");
//	unregister_chrdev(61,"sand1");

}

module_init(sand1_init);
module_exit(sand1_exit);


