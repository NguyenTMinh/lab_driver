#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

#define NUM_ARRAY 1000

static int array[NUM_ARRAY];

module_param_array(array, int, NULL, S_IRUGO);

/**
 * Tim min va max cua chuoi so
 * */
void findMinAndMaxArray(int arr[]) {
	int i, min = max = arr[0];
	int size = sizeof(arr) / sizeof(arr[0]);

	for (i = 1; i < size; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }

    printk(KERN_ALERT "lab1-bai2: min=%d, max=%d", min, max);
}

/**
 * Trung binh cong chuoi so
 * */
void ave(int arr[]) {
	int i, sum = 0;
	int size = sizeof(arr) / sizeof(arr[0]);

	for (i = 0; i < size; i++) {
		sum += arr[i];
	}

	float kq = sum/size;

	printk(KERN_ALERT "lab1-bai2: average=%f", kq);
}

int doInit(void) {
	findMinAndMaxArray(array);
	ave(array);
	return 0;
}

void doExit(void) {
	printk(KERN_ALERT "lab1-bai1. end");
}


module_init(doInit);
module_exit(doExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TRONG MINH");


