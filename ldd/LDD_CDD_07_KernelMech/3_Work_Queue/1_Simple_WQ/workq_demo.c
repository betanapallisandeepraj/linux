#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include "convenient.h"

static struct work_struct ws;

static void wq_func(void)
{
	MSG("We're here!\n");
}

static int workq_demo_init(void)
{
	INIT_WORK(&ws, wq_func);
	MSG("Now sleeping for 3s...\n");
	DELAY_SEC(3);
	schedule_work(&ws);
	//schedule_delayed_work(&ws, 3*HZ);

	MSG("Installed.\n");
	return 0;
}

static void workq_demo_exit(void)
{
	flush_scheduled_work ();
	MSG("Removed.\n");
}

MODULE_LICENSE("GPL");

module_init(workq_demo_init);
module_exit(workq_demo_exit);

