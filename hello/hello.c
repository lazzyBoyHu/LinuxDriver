#include <linux/init.h>
#include <linux/module.h>
static int hello_init(void)
{
    printk(KERN_ALERT "Hello, World\n");
    return 0;
}
static int hello_exit(void)
{
    printk(KERN_ALERT "GoodBye\n");
    return 0;
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL");
