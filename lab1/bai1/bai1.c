#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

#define NUM_ARRAY 1000

static int array[NUM_ARRAY];
static int a, b;
static int choice;

module_param_array(array, int, NULL, S_IRUGO);
module_param(b, int, S_IRUGO);
module_param(a, int, S_IRUGO);
module_param(choice, int, S_IRUGO);

/**
 * Ham tinh tong chuoi so
 * */
void sumOfArray(int arr[], int size) {
	int sum = 0;
	int i;

	for (i = 0; i < size; ++i)
	{
		sum += arr[i];
	}

	printk(KERN_ALERT "lab1-bai1. tong chuoi so = %d", sum);
}

/**
 * UCLN
 * */
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int doInit(void) {
	switch(choice) {
		case 1: {
			// tinh tong day so
			int n = sizeof(array) / sizeof(int);
			sumOfArray(array, n);
			break;
		}
		case 2: {
			// UCLN 2 so
			int kq = gcd(a, b);
			printk(KERN_ALERT "lab1-bai1. UCLN cua %d va %d = %d", a, b, kq);
			break;
		}
	}

	return 0;
}

void doExit(void) {
	printk(KERN_ALERT "lab1-bai1. end");
}


module_init(doInit);
module_exit(doExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TRONG MINH");


