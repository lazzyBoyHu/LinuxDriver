#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
static char *who = "world";
static int times = 1;
static int arry[6];
static int len;

module_param(times,int,S_IRUGO);
module_param(who,charp,S_IRUGO);
module_param_array(arry,int,&len,S_IRUGO);
static int param_init(void)
{
    int i;
    for(i=0;i<times;i++)
        printk(KERN_ALERT "(%d)Hello, %s!\n",i,who);
    printk(KERN_ALERT "\nlen = %d\n",len);
    for(i=0;i<len;i++)
        printk(KERN_ALERT"arry[%d] = %d\n",i,arry[i]);
    return 0;
}
static int param_exit(void)
{
    printk(KERN_ALERT "GoodBye,%s!\n",who);
    return 0;
}
module_init(param_init);
module_exit(param_exit);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("HT");
