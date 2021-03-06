#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/mm.h>
#include<linux/sched.h>
#include<linux/cdev.h>
#include<linux/kernel.h>
#include<asm/uaccess.h>


#define CDEV_DRV_MAJOR 231

#define BUFFER_MAX_SIZE_ 28

char buffer[BUFFER_MAX_SIZE_];

static int cdev_drv_open(struct inode *inode,struct file *fp)
{
    printk(KERN_ALERT"Open Successful!\n");
    printk(KERN_ALERT"Open Successful! BUFFER_MAX_SIZE_  %d \n", BUFFER_MAX_SIZE_ );
    return 0;
}

static int cdev_drv_release(struct inode *inode,struct file *fp)
{
    printk(KERN_ALERT"Close Successful!\n");
    return 0;
}

static ssize_t cdev_drv_read(struct file *fp,char __user *buf,size_t size,loff_t *pos)
{
    int ret = -EFAULT;
    unsigned int count = size;
    if (BUFFER_MAX_SIZE_ < size)
        count = BUFFER_MAX_SIZE_;
    if (!copy_to_user(buf,buffer,count))
    {
        printk(KERN_ALERT"read %d bytes ...\n",count);
        ret = count;
    }
    return ret;
}
static ssize_t cdev_drv_write(struct file *fp,const char __user *buf,size_t size,loff_t *pos)
{
    int ret = -EFAULT;
    unsigned int count = size;
    if (BUFFER_MAX_SIZE_ < size)
        count = BUFFER_MAX_SIZE_;
    printk(KERN_ALERT"Received %d \n", count);
    if (!copy_from_user(buffer,buf,count))
    {
        printk(KERN_ALERT"Received %d bytes : %s\n",count,buffer);
        ret = count;
    }
    return ret;
}

static const struct file_operations cdev_drv_fops =
{
    .owner = THIS_MODULE,
    .read = cdev_drv_read,
    .write = cdev_drv_write,
    .open = cdev_drv_open,
    .release = cdev_drv_release,
};

static int __init cdev_drv_init(void)
{
    int ret;

    printk("cdev_drv module is starting..\n");
    printk(KERN_ALERT"Open Successful! BUFFER_MAX_SIZE_  %d \n", BUFFER_MAX_SIZE_ );

    ret = register_chrdev(CDEV_DRV_MAJOR,"MYDEV",&cdev_drv_fops);
    if(ret < 0)
    {
        printk("register failed..\n");
        return 0;
    }
    else
    {
        printk("register success..\n");
    }
    return 0;
}
static void __exit cdev_drv_exit(void)
{
    printk("cdev_drv module is leaving..\n");
    unregister_chrdev(CDEV_DRV_MAJOR,"MYDEV");
}

module_init(cdev_drv_init);
module_exit(cdev_drv_exit);

MODULE_LICENSE("Dual BSD/GPL");
