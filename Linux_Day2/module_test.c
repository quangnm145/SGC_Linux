#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Peter Jay Salzman");

int myint = 420;

module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

static int __init hello_5_init(void)
{
	printk(KERN_INFO "Hello, world 5\n=============\n");
	printk(KERN_INFO "myint is an integer: %d\n", myint);
	return 0;
}

static void __exit hello_5_exit(void)
{
	printk(KERN_INFO "Goodbye, world 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);