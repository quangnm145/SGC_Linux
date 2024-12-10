#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("QuangNM41");
MODULE_DESCRIPTION("Test module A");

int x = 41;
EXPORT_SYMBOL(x);

module_param(x, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(x, "An integer");

static int __init moduleA_init(void)
{
    printk(KERN_INFO "Module A initialized.\n");
    printk(KERN_INFO "Module A declare x with value = %d\n", x);
    return 0;
}

static void __exit moduleA_exit(void)
{
    printk(KERN_INFO "Module A exited.\n");
}

module_init(moduleA_init);
module_exit(moduleA_exit);