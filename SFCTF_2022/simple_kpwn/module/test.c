#include <linux/input.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("brwook");
static ssize_t test_read(struct file *flip, char __user *buf, size_t count, loff_t *f_pos);
static ssize_t test_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos);

struct file_operations test_fops = {
    .read   = test_read,
    .write  = test_write,
};

static struct miscdevice test_driver = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "test",
    .fops = &test_fops,
};

static ssize_t test_read(struct file *flip, char __user *buf, size_t count, loff_t *f_pos)
{
    char arr[0x20] = { [0 ... 31] = 0 };
    char *ptr;
    unsigned char len;

    if(count > 32)
    {
        printk("size is too big!\n");
        return -1;
    }

    len = (unsigned char)count;
    len -= 1;
    
    ptr = (char *)kzalloc(len, GFP_KERNEL);
    memcpy(ptr, arr, len);

    if (copy_to_user(buf, ptr, len) != 0)
    {
        printk("copy error\n");
        return -1;
    }

    printk("test_read is done : %x", arr[0]);
    return 0;

}

static ssize_t test_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    char arr[0x40] = { [0 ... 63] = 0 };
    size_t len;
    char *ptr;

    if(count > 0x100)
    {
        printk("size is too big!\n");
        count = 0x100;
    }
    len = count;
    
    ptr = (char *)kmalloc(len, GFP_KERNEL);
    if (copy_from_user(ptr, buf, len) != 0)
    {
        printk("copy error\n");
        return -1;
    }
    memcpy(arr, ptr, len);
    printk("test_write is done : %x", arr[0]);
    return 0;
}

static int test_init(void)
{
    int result;
    result = misc_register(&test_driver);
    return 0;
}

static void test_exit(void)
{
    misc_deregister(&test_driver);
}

module_init(test_init);
module_exit(test_exit);

