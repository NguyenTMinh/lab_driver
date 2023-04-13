#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

#define NUM_ARRAY 1000


int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int doInit(void) {
	int arr[] = {12, 18, 24, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = arr[0];

    // tìm ƯCLN của tất cả các số trong chuỗi
    for (int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
    }

    printk(KERN_ALERT "lab1-bai4: kq=%d", result);
	return 0;
}

void doExit(void) {
	printk(KERN_ALERT "lab1-bai1. end");
}


module_init(doInit);
module_exit(doExit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TRONG MINH");


