#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/ktime.h>

#define DRIVER_AUTHOR "CNTT - KMA"
#define DRIVER_DESC   "Character driver don gian, cap phat dong, day du cac buoc"
#define MEM_SIZE 1024

// Bien
dev_t dev_num = 0;
static struct class * device_class;
static struct cdev *example_cdev;
uint8_t *kernel_buffer;
int length = 0; // Do dai du lieu luu

//function prototype cho entry point
static int example_open(struct inode *inode, struct file *filp);
static int example_release(struct inode *inode, struct file *filp);
static ssize_t example_read(struct file *filp, char __user *user_buf, size_t len, loff_t * off);
static ssize_t example_write(struct file *filp, const char *user_buf, size_t len, loff_t * off);

//dang ky Entry point voi file_operations 
static struct file_operations fops =
{
	.owner          = THIS_MODULE,
	.read           = example_read,
	.write          = example_write,
	.open           = example_open,
	.release        = example_release,
};
 
static int example_open(struct inode *inode, struct file *filp)
{
	printk("Handle opened event\n");
	return 0;
}

static int example_release(struct inode *inode, struct file *filp)
{
        printk("Handle closed event\n");
        return 0;
}
 
static ssize_t example_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	printk("Handle read event\n");
	printk("Choice: %zu\n", len);
	int choice = (int)len;
	char temp[1024];

	switch (choice) {
	case 1: {
		ktime_t abs_time = ktime_get_real();
		s64 abs_us_time = ktime_to_us(abs_time);
		sprintf(temp, "%lld", abs_us_time);
		break;
	}
	case 2: {
		ktime_t absolute_time = ktime_get_real();
    		s64 absolute_time_ns = ktime_to_ns(absolute_time);
		sprintf(temp, "%lld", absolute_time_ns);
		break;
	}
	case 3: {
		ktime_t relative_time = ktime_get();
    		s64 relative_time_ns = ktime_to_ns(relative_time);
		sprintf(temp, "%lld", relative_time_ns);
		break;
	}
	}

	copy_to_user(user_buf, temp, MEM_SIZE);
	return MEM_SIZE;
}

static ssize_t example_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off)
{
	printk("Handle write event\n");
	// Do nothing
	return len;
}

static int __init char_driver_init(void) {
	/*1 cap phat dong device number, va gan voi ten device*/
	alloc_chrdev_region(&dev_num, 0, 1, "tenDevice3.0");
	printk("Insert character driver successfully. major(%d), minor(%d)\n", MAJOR(dev_num), MINOR(dev_num));

	/*2 tao device file /dev/tenDeviceFile */
	device_class = class_create(THIS_MODULE, "lab52");

	device_create(device_class, NULL, dev_num, NULL,"lab5.2_NguyenTrongMinh");

	/* tao kernel buffer */
	kernel_buffer = kmalloc(MEM_SIZE , GFP_KERNEL);

	/*3 lien ket cac ham entry point cua driver voi device file */
	example_cdev = cdev_alloc();//cap phat bo nho cho bien cau truc cdev
	cdev_init(example_cdev, &fops); //khoi tao cho bien cau truc cdev
	cdev_add(example_cdev, dev_num, 1); //dang ky cau truc cdev voi kernel
	return 0;
}

void __exit char_driver_exit(void) {
	cdev_del(example_cdev);
	kfree(kernel_buffer);
	device_destroy(device_class,dev_num);
	class_destroy(device_class);
	unregister_chrdev_region(dev_num, 1);
	printk("Remove character driver successfully.\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION("3.0");
