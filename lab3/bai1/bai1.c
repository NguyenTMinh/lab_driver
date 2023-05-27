#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/string.h>
#include <linux/ctype.h>
#define MAX_SIZE 1024
#define COL 3
#define ROW 3

int choice, k, n;
int vector1[MAX_SIZE];
int vector2[MAX_SIZE];

module_param(choice, int, S_IRUGO);
module_param(k, int, S_IRUGO);
module_param(n, int, S_IRUGO);
module_param_array(vector1, int, NULL, 0644);
module_param_array(vector2, int, NULL, 0644);

// y a.
int tichVoHuong(void) {
	int size = sizeof(vector1) / sizeof(vector1[0]);
	int result = 0;
	int i;

    for (i = 0; i < size; i++) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

//y c
int giaithua(int n) {
    int result = 1;
    int i;

    for (i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int chinhhop(int N, int k) {
    if (k > N) {
        return 0;
    }
    return giaithua(N) / giaithua(N - k);
}

int __init doInit(void) {
	switch(choice) {
		case 1: {
			printk(KERN_INFO "lab3.bai1. tich vo huong: %d", tichVoHuong());
			break;
		}
		case 2: {
			printk(KERN_INFO "lab3.bai1. chinh hop: %d", chinhhop(n, k));
			break;
		} 
	}
	return 0;
}

void __exit doExit(void) {

}

module_init(doInit);
module_exit(doExit);
MODULE_LICENSE("GPL");