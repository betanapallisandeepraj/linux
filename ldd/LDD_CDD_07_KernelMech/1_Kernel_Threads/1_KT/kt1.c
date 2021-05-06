#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#define MODULE_NAME "kt"

/* Our simple kernel thread. */
static int
mykt (void *arg)
{
/* 
 * Daemonize: become a 'true' kernel thread: no attached user 
 * resources, 
 * close user­space pages (mm), block & flush all signals, 'inherit' 
 * init's open files..etc.
 */
//      daemonize("mykt");
  printk ("name: %s PID: %d TGID: %d\n", current->comm, current->pid,
	  current->tgid);
  if (!current->mm)
    printk ("mm field NULL.\n");
  allow_signal (SIGINT);
  allow_signal (SIGQUIT);
  while (1)
    {
      printk ("K Thread %d going to sleep now...\n", current->pid);
      set_current_state (TASK_INTERRUPTIBLE);
      schedule ();		// allows other parts of the kernel to run.
      // we're back on! has to be due to a signal
      if (signal_pending (current))
	break;
    }
  // We've been interrupted by a signal...
  set_current_state (TASK_RUNNING);
  printk ("K thread %d exiting now...\n", current->pid);
  return 0;

}

static int
hello_init (void)
{
  int ret;

  printk ("Create a kernel thread...\n");
  ret =
    kernel_thread (mykt, NULL,
		   CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD);
  /* 2nd arg is (void * arg) to pass, ret val is PID on success */
  if (ret < 0)
    {
      printk (KERN_ERR "kt1: kernel_thread failed.");
      return ret;
    }
  printk ("Module %s initialized, thread PID %d alive.\n", MODULE_NAME, ret);

  return 0;
}


static void
hello_exit (void)
{
  printk ("Module %s unloaded.\n", MODULE_NAME);
}

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Sandeep Raj");
MODULE_DESCRIPTION ("Android for Embedded Systems");
module_init (hello_init);
module_exit (hello_exit);
