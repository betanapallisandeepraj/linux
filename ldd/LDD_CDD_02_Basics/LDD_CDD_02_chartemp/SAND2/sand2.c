#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>

int sand2_open (struct inode *, struct file *);
ssize_t sand2_read (struct file *, char __user *, size_t, loff_t *);
ssize_t sand2_write (struct file *, const char __user *, size_t, loff_t *);
int sand2_close (struct inode *, struct file *);

struct file_operations sand2_ops = {
	.open = sand2_open,
	.read = sand2_read,
	.write = sand2_write,
	.release = sand2_close,
}; 

int sand2_open (struct inode *fptr, struct file *fptr2)
{
	printk("This is sand2_open function\n");
	return 0;
}
ssize_t sand2_read (struct file *fptr1, char __user *fptr2, size_t len, loff_t *fptr3)
{
	printk("This is sand2_read function\n");
	return 0;
}
ssize_t sand2_write (struct file *fptr1, const char __user *fptr2, size_t len, loff_t *fptr3)
{
	printk("This is sand2_write function\n");
	return len;

}
int sand2_close (struct inode *fptr1, struct file *fptr2)
{
	printk("This is sand2_close function\n");
	return 0;
}

static int sand2_init(void) {
	int ret;
	printk ("This is sand2 init function\n");
	ret = register_chrdev(61,"sand2",&sand2_ops);
	if (ret != 0)
	return -1;

	return 0;
}


static void sand2_exit(void) {
	printk ("This is sand2 exit function\n");
	unregister_chrdev(61,"sand2");

}

module_init(sand2_init);
module_exit(sand2_exit);
