#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/string.h>

int choice;
char my_string[1024];
char endChar[1];

module_param(choice, int, S_IRUGO);
module_param_string(endChar, endChar, sizeof(endChar), 0644);
module_param_string(my_string, my_string, sizeof(my_string), 0644);

// y 1
void lengthWithEndChar(void) {
	int i;

	for (i = 0; i < strlen(my_string); ++i)
	{
		if (my_string[i] == endChar[0]) {
			break;
		}
	}

	printk(KERN_INFO "do dai chuoi voi ki tu ket thuc duoc chi dinh: %d", i+1);
}

int __init doInit(void) {
	switch(choice) {
	case 1: {
		lengthWithEndChar();
		break;
	}
	}

	return 0;
}

void __exit doExit(void)
{
    printk(KERN_INFO "lab2.bai2 end\n");
}

module_init(doInit);
module_exit(doExit);