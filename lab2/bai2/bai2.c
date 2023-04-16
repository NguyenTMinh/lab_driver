#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/string.h>
#include <linux/ctype.h>

int choice;
char my_string[1024];
char my_string2[1024];
char endChar[2];
int lengthString;

module_param(choice, int, S_IRUGO);
module_param(lengthString, int, S_IRUGO);
module_param_string(endChar, endChar, sizeof(endChar), 0644);
module_param_string(my_string, my_string, sizeof(my_string), 0644);
module_param_string(my_string2, my_string2, sizeof(my_string2), 0644);

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

void reverseStringByLength(void) {
	int i;
	char subString[1024];
	char resString[1024];

	for (i = 0; i < lengthString; ++i)
	{
		subString[i] = my_string[i];
	}

	for (i = 0; i < lengthString; ++i)
	{
		resString[i] = subString[lengthString - i - 1];
	}

	printk(KERN_INFO "chuoi dao: %s", resString);

}

void reverseStringByEndChar(void) {
	int i;
	char subString[1024];
	char resString[1024];

	for (i = 0; i < strlen(my_string); ++i)
	{
		if (my_string[i] == endChar[0]) {
			subString[i] = my_string[i];
			break;
		}
		subString[i] = my_string[i];
	}

	int j;
	for (j = 0; j <= i; ++j)
	{
		resString[j] = subString[i - j];
	}

	printk(KERN_INFO "chuoi dao theo ki tu end: %s", resString);

}

//y 3
void standardizeString(void) {
	char resString[1024];
	int i;

	for (i = 0; i < strlen(my_string); ++i)
	{
		printk(KERN_INFO "ind: %d", i);
		if (isdigit(my_string[i])) {
			resString[i] = my_string[i];
		} else {
			if (i == 0 || i == strlen(my_string) - 1) {
				if (my_string[i] == '_') {
					continue;
				} else {
					if (i == 0) {
						resString[i] = toupper(my_string[i]);
					} else {
						resString[i] = tolower(my_string[i]);
					}
				}
			} else {
				if (my_string[i] == '_') {
					if (my_string[i+1] == '_') {
						resString[i] = my_string[i];
						
					} else {
						resString[i] = my_string[i];
					}
				} else {
					resString[i] = tolower(my_string[i]);
				}
			}
		}
	}

	printk(KERN_INFO "chuoi chuan hoa: %s", resString);
}

int __init doInit(void) {
	switch(choice) {
	case 1: {
		lengthWithEndChar();
		break;
	}
	case 2: {
		if (lengthString == 0) {
			reverseStringByEndChar();
		} else {
			reverseStringByLength();
		}
		break;
	}
	case 3: {
		standardizeString();
		break;
	} 
	case 4: {
		strcat(my_string, my_string2);
		printk(KERN_INFO "chuoi noi: %s", my_string);
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