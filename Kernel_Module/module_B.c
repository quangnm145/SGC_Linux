#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("QuangNM41");
MODULE_DESCRIPTION("Test module B");

extern int x;

static int __init moduleB_init(void)
{
    printk(KERN_INFO "Module B initialized.\n");
    printk(KERN_INFO "Module B take x from Module A = %d\n", x);
    return 0;
}

static void __exit moduleB_exit(void)
{
    printk(KERN_INFO "Module B exited.\n");
}

module_init(moduleB_init);
module_exit(moduleB_exit);