#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/kernel.h>

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
	char temp[length];
	int index = 0;
	int meet = 0;

	switch (choice) {
	case 3: {
		int i;
		for (i = 0; i < length; ++i)
		{
			if (meet == 1 && kernel_buffer[i] != ',') {
				temp[index++] = kernel_buffer[i];
			}

			if (kernel_buffer[i] == ',') {
				if (meet == 1) {
					temp[index] = '\0';
					break;
				}
				meet++;
			}
		}

		break;
	}
	case 4: {
		int i;
		for (i = 0; i < length; ++i)
		{
			if (meet == 2 && kernel_buffer[i] != ',') {
				temp[index++] = kernel_buffer[i];
			}

			if (kernel_buffer[i] == ',') {
				if (meet == 2) {
					temp[index] = '\0';
					break;
				}
				meet++;
			}
		}
		
		break;
	}
	case 5: {
		int i;
		for (i = 0; i < length; ++i)
		{
			if (meet == 3 && i != length) {
				temp[index++] = kernel_buffer[i];
			}

			if (kernel_buffer[i] == ',' || i == length - 1) {
				if (meet == 3) {
					temp[index] = '\0';
					break;
				}
				meet++;
			}
		}

		for (i = 0; i < index; ++i)
		{
			printk("Data: %c\n", temp[i]);
		}
		
		break;
	}
	}

	copy_to_user(user_buf, temp, MEM_SIZE);
	return MEM_SIZE;
}

// Xu ly khi nguoi dung nhap so vao -> chuyen doi
static ssize_t example_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off)
{
	printk("Handle write event\n");
	copy_from_user(kernel_buffer, user_buf, len);

	// Xu ly chuyen doi he so
	// Convert sang so thap phan tu input
	int number = 0;
	int index_ker_buf = 0;
	kstrtoint(kernel_buffer, 10, &number);
	int tempNum = number;

	// Lay do dai cua so
	length = 0;
	if (number == 0) {
		length = 1;
	} else {
		while (tempNum != 0) {
			tempNum /= 10;
			length++;
		}
	}

	// ======= 10 sang 2 =======
	char bits[32];
	int index = 0;
	tempNum = number;

	if (tempNum != 0) {
		while (tempNum > 0) {
			bits[index++] = tempNum%2 + '0';
			tempNum /= 2;
		}

		int i, j=0;
		kernel_buffer[length++] = ',';
		for (i = length; i < (length + index); ++i)
		{
			kernel_buffer[i] = bits[index-j-1];
			j++;
		}

		length += index;
	}

	// ======= 10 sang 8 =======
	char octs[32];
	index = 0;
	tempNum = number;

	if (tempNum != 0) {
		while (tempNum > 0) {
			octs[index++] = tempNum%8 + '0';
			tempNum /= 8;
		}

		int i, j=0;
		kernel_buffer[length++] = ',';
		for (i = length; i < (length + index); ++i)
		{
			kernel_buffer[i] = octs[index-j-1];
			j++;
		}

		length += index;
	}

	// ======= 10 sang 16 =======
	char hexs[32];
	tempNum = number;
	index = 0;

	if (tempNum != 0) {
		while (tempNum != 0) {
			int remainder = tempNum % 16;
			if (remainder < 10) {
				hexs[index] = remainder + '0';
			} else {
				hexs[index] = remainder - 10 + 'A' ;
			}
			tempNum /= 16;
			index++;
		}

		int i, j=0;
		kernel_buffer[length++] = ',';
		for (i = length; i < (length + index); ++i)
		{
			kernel_buffer[i] = hexs[index-j-1];
			j++;
		}

		length += index;
	}

	return len;
}

static int __init char_driver_init(void) {
	/*1 cap phat dong device number, va gan voi ten device*/
	alloc_chrdev_region(&dev_num, 0, 1, "tenDevice3.0");
	printk("Insert character driver successfully. major(%d), minor(%d)\n", MAJOR(dev_num), MINOR(dev_num));

	/*2 tao device file /dev/tenDeviceFile */
	device_class = class_create(THIS_MODULE, "lab51");

	device_create(device_class, NULL, dev_num, NULL,"lab5.1_NguyenTrongMinh");

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
